matrix WVPMatrix; // �ϊ��s��
vector LightDirection; // ���̕���

struct S00_INPUT // ���͒��_
{
    vector position : POSITION;
    vector normal   : NORMAL;
};

struct S00_OUTPUT // �o�͒��_
{
    vector position : POSITION;
    vector diffuse : COLOR;
};

S00_OUTPUT Main(S00_INPUT input)
{
    S00_OUTPUT output = (S00_OUTPUT) 0; // output�s���������
    
    output.position = input.position;

    output.position = mul(output.position, WVPMatrix); // ���_��3�ϊ�����
    output.diffuse = dot((-LightDirection), input.normal); // �@���ŐF���v�Z
    
    return output;
}