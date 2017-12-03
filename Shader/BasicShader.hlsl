matrix WVPMatrix;	// ���[���h�A�r���[�A�v���W�F�N�V�����ϊ��}�g���b�N�X
vector color;					// ���_�J���[

struct VS_INPUT	// ���͒��_�\����
{
	vector position:POSITION;
};

struct VS_OUTPUT	// �o�͒��_�\����
{
	vector position : POSITION;
	vector color:COLOR;
};

VS_OUTPUT SetColor(VS_INPUT input)	// �J���[�ݒ�ƂR�ϊ�
{
	VS_OUTPUT output = (VS_OUTPUT)0;	// �}�g���b�N�X��������

	output.position = mul(input.position, WVPMatrix);	// 2�}�g���b�N�X������
	output.color = color;	// �J���[��ݒ�

	return output;
}