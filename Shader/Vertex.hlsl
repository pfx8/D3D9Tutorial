matrix WVPMatrix;	// ���[���h�A�r���[�A�v���W�F�N�V�����ϊ��}�g���b�N�X

vector LightDirection;	// ���̕����x�N�g��
vector Scalar;		// ���[�t�B���O�v�Z
					// T�����ԁAt�ϊ�����
					// Scalar = t / T
					// C = A * (1-S) + B * S

struct VS_INPUT	// ���͒��_�\����
{
	// 1st���_stream
	vector position	: POSITION;
	vector normal		: NORMAL;

	// 2nd���_stream
	vector position1	: POSITION1;
	vector normal1	: NORMAL;

	// �e�N�X�`�����W  
	float2 uvCoords	: TEXCOORD;
};

struct VS_OUTPUT	// �o�͒��_�\����
{
	vector position	: POSITION;
	vector diffuse	: COLOR;
	float2 uvCoords	: TEXCOORD;
};

VS_OUTPUT SetColor(VS_INPUT input)	// �J���[�ݒ�ƂR�ϊ�
{
	VS_OUTPUT output = (VS_OUTPUT)0;	// �}�g���b�N�X��������

	output.position = input.position*Scalar.x + input.position1*Scalar.y;	// ���_�v�Z
	output.position = mul(output.position, WVPMatrix);					// 3�ϊ�

	vector normal = input.normal * Scalar.x + input.position1 * Scalar.y;	// �@���v�Z
    output.diffuse = dot((-LightDirection), normal);	// �@���ƌ��̓��ς��v�Z���āA�F�����߂�

    output.uvCoords = input.uvCoords;

	return output;
}