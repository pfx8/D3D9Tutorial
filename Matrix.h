//*****************************************************************************
//
// �}�g���b�N�X���� [Matrix.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Engine.h"

class Matrix
{
private:

public:
	Matrix();
	~Matrix();

	D3DXMATRIX	m_TSMatrix;	// �ړ��A�g��k���s��
	void SetTSMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 scl);

	D3DXMATRIX	m_rotMatrix;	// ��]�s��
	void SetRotMatrix(float rot, char axis);
};

#endif // !_MATRIX_H_
