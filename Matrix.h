//*****************************************************************************
//
// マトリックス処理 [Matrix.h]
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

	D3DXMATRIX	m_TSMatrix;	// 移動、拡大縮小行列
	void SetTSMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 scl);

	D3DXMATRIX	m_rotMatrix;	// 回転行列
	void SetRotMatrix(float rot, char axis);
};

#endif // !_MATRIX_H_
