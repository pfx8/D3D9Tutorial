struct VS_OUTPUT
{
    float2 position	: POSITIONT;
    float2 uvCoords	: TEXCOORD0; // テクスチャ座標
};

// 頂点シェーダー
VS_OUTPUT RHWVertexShader(float2 pos : POSITIONT,
                            float2 uvCoords : TEXCOORD0)
{
    VS_OUTPUT vout = (VS_OUTPUT) 0;

    // 画面座標なので、ここで変更とか一切なし
    vout.position = pos;
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
        //VertexShader = compile vs_3_0 RHWVertexShader();
        PixelShader = compile ps_3_0 RHWPixelShader();
    }
}