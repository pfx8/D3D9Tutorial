//*****************************************************************************
//
// 画面座標処理 [RHWShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

texture tex; // テクスチャ
sampler Samp = // サンプラー
sampler_state
{
    Texture = <tex>;
    //MipFilter = LINEAR;
    //MinFilter = LINEAR;
    //MagFilter = LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

float4 RHWPixelShader(float2 pos : POSITIONT,
                            float2 uvCoords : TEXCOORD0) : COLOR0
{
    float4 diffuse = tex2D(Samp, uvCoords);
    //diffuse.a = 0.3;

    return diffuse;
}

//------------------------------------------------------
// エフェクト
//------------------------------------------------------
technique RHWRender
{
	pass P0
	{
        // POSITIONTなので、頂点シェーダーの処理をされてない
        PixelShader = compile ps_3_0 RHWPixelShader();

        // ディフェーズ透明度を使用にする
        AlphaBlendEnable = True;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
    }
}