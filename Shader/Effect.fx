//------------------------------------------------------
// 頂点シェーダー(テクスチャ付き)
//------------------------------------------------------
matrix WVPMatrix;
float3 LightDirection;

struct VS_INPUT
{
    float3 position	: POSITION0;
    float3 normal	: NORMAL0;
    float4 diffuse	: COLOR0;
    float2 uvCoords	: TEXCOORD0; // テクスチャ座標
};

struct VS_OUTPUT
{
    float4 position : POSITION0;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
    float2 uvCoords : TEXCOORD0; // テクスチャ座標
};

VS_OUTPUT VS_Main(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT) 0;
    Out.position = mul(float4(In.position, 1.0f), WVPMatrix);
    Out.normal = In.normal;
    //Out.diffuse = In.diffuse;
    //Out.diffuse = dot((-LightDirection), In.normal); // 法線と光の内積を計算して、色を決める
	Out.uvCoords = In.uvCoords;

	return Out;
}

//------------------------------------------------------
// 頂点シェーダー(テクスチャ付いてない)
//------------------------------------------------------
struct VS_NT_INPUT
{
    float3 position : POSITION;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
};

struct VS_NT_OUTPUT
{
    float4 position : POSITION0;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
};

VS_NT_OUTPUT VS_NT_Main(VS_NT_INPUT In)
{
    VS_NT_OUTPUT Out = (VS_NT_OUTPUT) 0; // 初期化
    Out.position = mul(float4(In.position, 1.0f), WVPMatrix);
    Out.normal = In.normal;

    return Out;
}

//------------------------------------------------------
// ピクセルシェーダー
//------------------------------------------------------
texture Tex;   // 使用するテクスチャ
sampler Samp = // サンプラー
sampler_state
{
    Texture = <Tex>;
};

float4 PS_Main(VS_OUTPUT In):COLOR0
{
    return tex2D(Samp, In.uvCoords);
}

float4 PS_NT_Main(VS_NT_OUTPUT In) : COLOR0
{
    float value = dot((-LightDirection), In.normal); // 法線と光の内積を計算して、色を決める;
    float4 color = float4(1.0, 0, 0, 1.0);           // 赤

    if(value >0.95)
        color = float4(1.0, 1.0, 1.0, 1.0) * color;
    else if(value >0.7)
        color = float4(0.7, 0.7, 0.7, 1.0) * color;
    else if (value >0.25)
        color = float4(0.3, 0.3, 0.3, 1.0) * color;
    else
        color = float4(0.2, 0.2, 0.2, 1.0) * color;

    return color; // 法線と光の内積を計算して、色を決める;
}

//------------------------------------------------------
// エフェクト
//------------------------------------------------------
technique BasicShader
{
	pass P0
	{
        VertexShader = compile vs_3_0 VS_Main();
        PixelShader = compile ps_2_0 PS_Main();
    }
}

technique NoTextureShader   // テクスチャついてない
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS_NT_Main();
        PixelShader = compile ps_3_0 PS_NT_Main();
    }
}