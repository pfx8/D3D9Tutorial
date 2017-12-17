//*****************************************************************************
//
// 島の地面処理 [Island.h]
//
//*****************************************************************************
#ifndef _ISLAND_H_
#define _ISLAND_H_

#include "Modules/Plane.h"

class IsLand : public Plane
{
private:
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;	// 頂点インデックスバッファ

public:

	void InitIsland(D3DXVECTOR3 centerPos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);
	void Update();
	void Draw();
};
#endif // !_ISLAND_H_
