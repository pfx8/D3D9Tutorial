//*****************************************************************************
//
// 画面座標処理 [RHWShader.fx]
//
// コンパイルはしない
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
int     type;  // 船の状態
float   alpha; // 弾発射ボタン処理

//sampler2D Texture0;
//float fDissolve : SinTime0_X;

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

float4 RHWPixelShader(float2 pos : POSITIONT,
                      float2 uvCoords : TEXCOORD0) : COLOR0
{
    float4 diffuse = tex2D(Samp, uvCoords);

    if (type == 1) // 船の状態
    {
        diffuse.r = 0.84;
    }
    
    if (type == 2)
    {
        diffuse *= alpha;
    }

    return diffuse;
    }

//float4 ps_main(float2 tex : TEXCOORD0) : COLOR0
//{
//    float4 color = tex2D(Texture0, tex);
//    clip(color.r + fDissolve * 0.15f);
//    return color;
//}

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