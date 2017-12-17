matrix WVPMatrix;
float3 LightDirection;

//------------------------------------------------------
// BsaicShader(テクスチャ付き)
//------------------------------------------------------
struct BasicVertexIN
{
    float3 position	: POSITION0;
    float3 normal	: NORMAL0;
    float4 diffuse	: COLOR0;
    float2 uvCoords	: TEXCOORD0; // テクスチャ座標
};

struct BasicVertexOUT
{
    float4 position : POSITION0;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
    float2 uvCoords : TEXCOORD0; // テクスチャ座標
};

texture Tex; // 使用するテクスチャ
sampler Samp = // サンプラー
sampler_state
{
    Texture = <Tex>;
};

// 頂点シェーダー
BasicVertexOUT BasicVertexShader(BasicVertexIN In)
{
	BasicVertexOUT Out = (BasicVertexOUT) 0;
    Out.position = mul(float4(In.position, 1.0f), WVPMatrix);
    Out.normal = In.normal;
	Out.uvCoords = In.uvCoords;

	return Out;
}

// ピクセルシェーダー
float4 BasicPixelShader(BasicVertexOUT In) : COLOR0
{
    return tex2D(Samp, In.uvCoords);
}



//------------------------------------------------------
// トゥ―ンシェーダー(テクスチャ付いてない)
//------------------------------------------------------
struct CelVertexIN
{
    float3 position : POSITION;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
};

struct CelVertexOUT
{
    float4 position : POSITION0;
    float3 normal   : NORMAL0;
    float4 diffuse  : COLOR0;
};

// モデル
// 頂点シェーダー
CelVertexOUT CelVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化
    Out.position = mul(float4(In.position, 1.0f), WVPMatrix);
    //Out.normal = normalize(mul(float4(In.normal, 1.0f), WVPMatrix));
    Out.normal = In.normal;

    return Out;
}
// ピクセルシェーダー
float4 CelPixelShader(CelVertexOUT In) : COLOR0
{
    float value = dot(-LightDirection, In.normal); // 法線と光の内積を計算して、色を決める;
    float4 color = float4(1.0, 0.0, 0.0, 1.0); // 赤

    if(value >0.45)
        color = float4(1.0, 1.0, 1.0, 1.0) * color;
    else if(value >0.2)
        color = float4(0.7, 0.7, 0.7, 1.0) * color;
    else
        color = float4(0.3, 0.3, 0.3, 1.0) * color;

    return color; // 法線と光の内積を計算して、色を決める;
}

// アウトライン
// 頂点シェーダー
CelVertexOUT OutlineVertexShader(CelVertexIN In)
{
    CelVertexOUT Out = (CelVertexOUT) 0; // 初期化

    float4 position = mul(float4(In.position, 1.0f), WVPMatrix);
    float4 normal = normalize(mul(float4(In.normal, 1.0f), WVPMatrix));

    Out.position = position + (mul(0.3, normal)); // 意味は？

    return Out;
}
// ピクセルシェーダー
float4 OutlinePixelShader(CelVertexOUT In) : COLOR0
{
    return float4(0, 0, 0, 1); // 法線と光の内積を計算して、色を決める;
}

//------------------------------------------------------
// エフェクト
//------------------------------------------------------
technique BasicShader
{
	pass P0
	{
        VertexShader = compile vs_3_0 BasicVertexShader();
        PixelShader = compile ps_2_0 BasicPixelShader();
    }
}

technique CelShader // トゥ―ンシェーダー
{
    //pass P0 // OutLine
    //{
    //    VertexShader = compile vs_3_0 OutlineVertexShader();
    //    PixelShader = compile ps_3_0 OutlinePixelShader();
    //}
    pass P0 // モデル
    {
        VertexShader = compile vs_3_0 CelVertexShader();
        PixelShader = compile ps_3_0 CelPixelShader();
    }
}