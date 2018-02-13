//*****************************************************************************
//
// デフォルトシェーダー [BasicShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

float    alpha; // カラーアルファ値

float4x4 WMatrix : WORLD;
float4x4 VPMatrix : VIEWPROJECTION;

struct VS_OUTPUT
{
    float4 position	: POSITION0;
    float2 uvCoords	: TEXCOORD0; // テクスチャ座標
};

// 頂点シェーダー
VS_OUTPUT BasicVertexShader(float4 pos : POSITION0,
                            float2 uvCoords : TEXCOORD0)
{
    VS_OUTPUT vout = (VS_OUTPUT) 0;

    // ワールド変換、ビューイング変換、プロジェクション変換
    vout.position = mul(pos, WMatrix);
    vout.position = mul(vout.position, VPMatrix);
    vout.uvCoords = uvCoords;

	return vout;
}


//////////////////////////////////////////////////////////////////////////
texture tex; // テクスチャ
sampler Samp = // サンプラー
sampler_state
{
    Texture = <tex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

struct PS_OUTPUT
{
    float4 diffuse : COLOR0;
};

// ピクセルシェーダー
PS_OUTPUT BasicPixelShader(VS_OUTPUT vsout, uniform bool withTextrue)
{
    PS_OUTPUT pout = (PS_OUTPUT) 0;

    if (withTextrue == true)
    {
        pout.diffuse = tex2D(Samp, vsout.uvCoords + float2(0.5f, 0.5f)) * alpha; // textrue sRGB * Alpha
    }
    else
    {
        pout.diffuse = float4(1.0, 0.0, 0.0, 1.0) * alpha; // 赤を出る
    }

    return pout;
}

//------------------------------------------------------
// エフェクト
//------------------------------------------------------
technique RenderWithoutTextrue
{
	pass P0
	{
        VertexShader = compile vs_3_0 BasicVertexShader();
        PixelShader = compile ps_3_0 BasicPixelShader(false);
    }
}

technique RenderWithTextrue
{
    pass P0
    {
        VertexShader = compile vs_3_0 BasicVertexShader();
        PixelShader = compile ps_3_0 BasicPixelShader(true);

        CullMode = NONE; // 両面
    }
}