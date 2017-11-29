//*****************************************************************************
//
// �}�g���b�N�X���� [Matrix.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Matrix.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Matrix::Matrix()
{
	D3DXMatrixIdentity(&m_TSMatrix);
	D3DXMatrixIdentity(&m_rotMatrix);
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Matrix::~Matrix()
{

}

//*****************************************************************************
// ������Mt * Mt
//
// �ړ��s��Mt			// �g��k���s��Ms		// Mt * Ms
// [ 1  0  0  Tx]		// [ Sx 0  0  0 ]		// [ Sx 0  0  Tx ]
// [ 0  1  0  Ty]		// [ 0  Sy 0  0 ]		// [ 0  Sy 0  Ty ]
// [ 0  0  1  Tz]		// [ 0  0  0  Sz]		// [ 0  0  Sz Tz ]
// [ 0  0  0   1]		// [ 0  0  0  1 ]		// [ 0  0  0  1  ]
//*****************************************************************************
void Matrix::SetTSMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 scl)
{
	// �ړ�
	m_TSMatrix._14 = pos.x;
	m_TSMatrix._24 = pos.y;
	m_TSMatrix._34 = pos.z;

	// �g��k��
	m_TSMatrix._11 = scl.x;
	m_TSMatrix._22 = scl.y;
	m_TSMatrix._33 = scl.z;
}

//*****************************************************************************
// ������
//
// ��]�s��Mrx		// ��]�s��Mry		// ��]�s��Mrz
// [ 1  0    0  0 ]	// [  cos  0  sin 0 ]	// [ cos -sin  0  0 ]
// [ 0 cos -sin 0 ]	// [   0   1   0  0 ]	// [ sin  cos  0  0 ]
// [ 0 sin  cos 0 ]	// [ -sin  0  cos 0 ]	// [  0    0   1  0 ]
// [ 0  0    0  1 ]	// [   0   0   0  1 ]	// [  0    0   0  1 ]
//*****************************************************************************
void Matrix::SetRotMatrix(float rot, char axis)
{
	switch (axis)
	{
	case 'x':
	case 'X':
		m_rotMatrix._22 = cosf(D3DXToRadian(rot));
		m_rotMatrix._23 = -sinf(D3DXToRadian(rot));
		m_rotMatrix._32 = sinf(D3DXToRadian(rot));
		m_rotMatrix._33 = cosf(D3DXToRadian(rot));
		break;
	case 'y':
	case 'Y':
		m_rotMatrix._11 = cosf(D3DXToRadian(rot));
		m_rotMatrix._13 = sinf(D3DXToRadian(rot));
		m_rotMatrix._31 = -sinf(D3DXToRadian(rot));
		m_rotMatrix._33 = cosf(D3DXToRadian(rot));
		break;
	case 'z':
	case 'Z':
		m_rotMatrix._11 = cosf(D3DXToRadian(rot));
		m_rotMatrix._12 = -sinf(D3DXToRadian(rot));
		m_rotMatrix._21 = sinf(D3DXToRadian(rot));
		m_rotMatrix._22 = cosf(D3DXToRadian(rot));
	default:
		break;
	}
}