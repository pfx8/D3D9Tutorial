//*****************************************************************************
//
// ���̒n�ʏ��� [Island.h]
//
//*****************************************************************************
#ifndef _ISLAND_H_
#define _ISLAND_H_

#include "Modules/Plane.h"

class IsLand : public Plane
{
private:
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;	// ���_�C���f�b�N�X�o�b�t�@

public:

	void InitIsland(D3DXVECTOR3 centerPos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);
	void Update();
	void Draw();
};
#endif // !_ISLAND_H_
