vector Scalar;	// ������䗦
                // Scalar.x texture0
                // Scalar.y texture1

texture Tex0;   // �e�N�X�`��0
texture Tex1;   // �e�N�X�`��1

// �T���v���[0
sampler Samp0 = 
sampler_state
{
    Texture = <Tex0>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

// �T���v���[1
sampler Samp1 = 
sampler_state
{
    Texture = <Tex1>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

struct PS_INPUT	// ���͒��_�\����
{
	float2 uvCoords0	: TEXCOORD0; // �e�N�X�`��0���W 
	float2 uvCoords1	: TEXCOORD1; // �e�N�X�`��1���W
};

struct PS_OUTPUT	// �o�͒��_�\����
{
	float4 Color : COLOR0;
};

PS_OUTPUT Main(PS_INPUT input)	// �J���[�ݒ�ƂR�ϊ�
{
    PS_OUTPUT output = (PS_OUTPUT) 0; // �o�͒��_�\���̂�������
    output.Color = tex2D(Samp0, input.uvCoords0)*Scalar.x + tex2D(Samp1, input.uvCoords1)*Scalar.y;	// ���������F���v�Z
	return output;
}