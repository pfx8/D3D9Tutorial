/////////////////////////////////////////////////////////
// 頂点シェーダー
////////////////////////////////////////////////////////
matrix WVPMatrix;
//vector LightDirection;

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
    Out.diffuse = In.diffuse;
	Out.uvCoords = In.uvCoords;

	return Out;
}

/////////////////////////////////////////////////////////
// ピクセルシェーダー
////////////////////////////////////////////////////////
texture Tex;        // 使用するテクスチャ
sampler Samp =      // サンプラー
sampler_state
{
    Texture = <Tex>;
};

//struct PS_INPUT
//{
//    float2 TexCoord : TEXCOORD0;
//};

//struct PS_OUTPUT
//{
//    float4 color : COLOR0;
//};

//PS_OUTPUT PS_Main(PS_INPUT In)
//{
//    PS_OUTPUT Out = (PS_OUTPUT) 0;
//    Out.color = tex2D(Samp, In.TexCoord);
//    return Out;
//}

float4 PS_Main(VS_OUTPUT In):COLOR0
{
    return tex2D(Samp, In.uvCoords);
}

/////////////////////////////////////////////////////////
// エフェクト
////////////////////////////////////////////////////////
technique T0
{
	pass P0 // 平面(テクスチャ付き)
	{
        VertexShader = compile vs_3_0 VS_Main();
        PixelShader = compile ps_2_0 PS_Main();
    }
    pass P1
    {

    }
}