vector Scalar;	// 混ざり比率
                // Scalar.x texture0
                // Scalar.y texture1

texture Tex0;   // テクスチャ0
texture Tex1;   // テクスチャ1

// サンプラー0
sampler Samp0 = 
sampler_state
{
    Texture = <Tex0>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// サンプラー1
sampler Samp1 = 
sampler_state
{
    Texture = <Tex1>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

struct PS_INPUT	// 入力頂点構造体
{
	float2 uvCoords0	: TEXCOORD0; // テクスチャ0座標 
	float2 uvCoords1	: TEXCOORD1; // テクスチャ1座標
};

struct PS_OUTPUT	// 出力頂点構造体
{
	float4 Color : COLOR0;
};

PS_OUTPUT Main(PS_INPUT input)	// カラー設定と３つ変換
{
    PS_OUTPUT output = (PS_OUTPUT) 0; // 出力頂点構造体を初期化
    output.Color = tex2D(Samp0, input.uvCoords0)*Scalar.x + tex2D(Samp1, input.uvCoords1)*Scalar.y;	// 混ざった色を計算
	return output;
}