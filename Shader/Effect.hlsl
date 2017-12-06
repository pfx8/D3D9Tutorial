/////////////////////////////////////////////////////////
// 頂点シェーダー
////////////////////////////////////////////////////////
matrix WVPMatrix;
vector LightDirection;

struct VS_INPUT
{
    vector position	: POSITION;
    vector normal		: NORMAl;
    vector diffuse	: COLOR;
    float2 uvCoords	: TEXCOORD; // テクスチャ座標
};

struct VS_OUTPUT
{
	vector position	: POSITION;
	vector normal		: NORMAl;
	vector diffuse	: COLOR;
    float2 uvCoords	: TEXCOORD; // テクスチャ座標
};

VS_OUTPUT VS_Main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;
	output.position = mul(input.position, WVPMatrix);
    output.normal = input.normal;
    output.diffuse = input.diffuse;
	output.uvCoords = input.uvCoords;

	return output;
}

/////////////////////////////////////////////////////////
// ピクセルシェーダー
////////////////////////////////////////////////////////
texture Tex;

sampler Samp =
sampler_state
{
    Texture = <Tex>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

struct PS_INPUT
{
    float2 uvCoords : TEXCOORD;
};

struct PS_OUTPUT
{
    float4 Color : COLOR0;
};

PS_OUTPUT PS_Main(PS_INPUT input)
{
    PS_OUTPUT output = (PS_OUTPUT) 0;
    output.Color = tex2D(Samp, input.uvCoords);

    return output;
}

/////////////////////////////////////////////////////////
// エフェクト
////////////////////////////////////////////////////////
technique T0
{
	pass P0
	{
        VertexShader = compile vs_1_1 VS_Main();
        PixelShader = compile ps_2_0 PSVS_Main();
    }
}