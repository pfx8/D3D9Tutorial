//*****************************************************************************
//
// シャドーマップ処理 [ShadowMapShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#define SMAP_SIZE (512)

#define SHADOW_EPSILON 0.00005f

// シャドーマップ頂点IN構造体
struct ShadowMapVertexIN
{
    float3 position : POSITION;
    float3 normal : NORMAL0;
};

// シャドーマップ頂点OUT構造体
struct ShadowMapVertexOUT
{
    float4 position : POSITION;
    float2 depth : TEXCOORD0;
};

// シャドー頂点IN構造体
struct ShadowVertexIN
{
    float3 position : POSITION;
    float3 normal : NORMAL0;
    float2 uvcoord : TEXCOORD0;
};

// シャドー頂点OUT構造体
struct ShadowVertexOUT
{
    float4 position : POSITION;
    float2 uvcoord : TEXCOORD0;
    float4 vposition : TEXCOORD1;
    float3 normal : TEXCOORD2;
    float4 posLight : TEXCOORD3;
};

// 行列
matrix WVMatrix; // ワールド変換とビューイング変換行列
matrix PMatrix; // プロジェクション変換行列
matrix ViewToLightProj; //

// ライト
float3 lightPos;
float3 lightDir; // ライト方向ベクトル
float4 lightAmbient; // 拡散反射光(モデル本来のカラー)

// マテリアル
float4 material;

// 
float cosTheta;

// サンプラー
sampler2D sceneSample =
sampler_state
{
    Texture = <sceneTex>;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D shadowSample =
sampler_state
{
    Texture = <shadowTex>;
    MinFilter = Point;
    MagFilter = Point;
    MipFilter = Point;
    AddressU = Clamp;
    AddressV = Clamp;
};

//------------------------------------------------------
//
// 頂点シェーダー
//
// シャドーマップを生成
//
//------------------------------------------------------
ShadowMapVertexOUT ShadowMapVertexShader(ShadowMapVertexIN In)
{
    ShadowMapVertexOUT Out = (ShadowMapVertexOUT) 0;

    Out.position = mul(float4(In.position, 1.0), WVMatrix);
    Out.position = mul(Out.position, PMatrix);

    // 深さを取得
    Out.depth.xy = Out.position.zw;

    return Out;
}

//------------------------------------------------------
//
// ピクセルシェーダー
//
// シャドーマップを生成
//
//------------------------------------------------------
float4 ShadowMapPixelShader(ShadowMapVertexOUT Out) : COLOR
{
    float4 color = Out.depth.x / Out.depth.y;
    return color;
}

//------------------------------------------------------
//
// 頂点シェーダー
//
// シャドーを生成
//
//------------------------------------------------------
ShadowVertexOUT ShadowVertexShader(ShadowVertexIN In)
{
    ShadowVertexOUT Out = (ShadowVertexOUT) 0;
    
    Out.vposition = mul(float4(In.position, 1.0), WVMatrix);
    Out.position = mul(Out.vposition, PMatrix);

    Out.normal = mul(In.normal, (float3x3)WVMatrix);

    Out.uvcoord = In.uvcoord;

    Out.posLight = mul(Out.vposition, ViewToLightProj);
}

//------------------------------------------------------
//
// ピクセルシェーダー
//
// シャドーを生成
//
//------------------------------------------------------
float4 ShadowPixelShader(ShadowVertexOUT Out) : COLOR
{
    float4 diffuse;

    float3 light = normalize((float3)Out.vposition - lightPos);

    if (dot(light, lightDir) > cosTheta)
    {
        float2 ShadowTexC = 0.5 * Out.posLight.xy / Out.posLight.w + float2(0.5, 0.5);
        ShadowTexC.y = 1.0f - ShadowTexC.y;

        // transform to texel space
        float2 texelpos = SMAP_SIZE * ShadowTexC;
        
        // Determine the lerp amounts           
        float2 lerps = frac( texelpos );

        //read in bilerp stamp, doing the shadow checks
        float sourcevals[4];
        sourcevals[0] = (tex2D( shadowSample, ShadowTexC) + SHADOW_EPSILON < Out.posLight.z / Out.posLight.w) ? 0.0f : 1.0f;
        sourcevals[1] = (tex2D( shadowSample, ShadowTexC + float2(1.0/SMAP_SIZE, 0) ) + SHADOW_EPSILON < Out.posLight.z / Out.posLight.w)? 0.0f: 1.0f;  
        sourcevals[2] = (tex2D( shadowSample, ShadowTexC + float2(0, 1.0 / SMAP_SIZE)) + SHADOW_EPSILON < Out.posLight.z / Out.posLight.w) ? 0.0f : 1.0f;
        sourcevals[3] = (tex2D( shadowSample, ShadowTexC + float2(1.0 / SMAP_SIZE, 1.0 / SMAP_SIZE)) + SHADOW_EPSILON < Out.posLight.z / Out.posLight.w) ? 0.0f : 1.0f;
        
        // lerp between the shadow values to calculate our light amount
        float LightAmount = lerp( lerp( sourcevals[0], sourcevals[1], lerps.x ),
                                  lerp( sourcevals[2], sourcevals[3], lerps.x ),
                                  lerps.y );
        // Light it
        diffuse = (saturate(dot(-light, normalize(Out.normal))) * LightAmount * (1 - lightAmbient) + lightAmbient)
                  * material;
    }
    else
    {
        diffuse = lightAmbient * material;
    }

    return tex2D(sceneSample, Out.uvcoord) * diffuse;

}

//------------------------------------------------------
// エフェクト
//------------------------------------------------------
technique ShadowRender
{
	pass P0
	{
        VertexShader = compile vs_3_0 ShadowMapVertexShader();
        PixelShader = compile ps_3_0 ShadowMapPixelShader();
    }
}

