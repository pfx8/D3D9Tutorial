texture tex; // テクスチャ
sampler Samp = // サンプラー
sampler_state
{
    Texture = <tex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

float4 RHWPixelShader(float2 pos : POSITIONT,
                            float2 uvCoords : TEXCOORD0) : COLOR0
{
    //return float4(1.0, 0.0, 0.0, 1.0);
    return tex2D(Samp, uvCoords);
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
    }
}