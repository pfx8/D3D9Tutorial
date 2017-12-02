//*****************************************************************************
//
// メッシュ処理 [Mesh.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "Engine.h"

#include "Material.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Mesh
{
private:


public:
	LPD3DXMESH		m_mesh;				// メッシュ情報へのポインタ
	PDIRECT3DTEXTURE9	m_meshTexturePoint;	// テクスチャマネジメント
	Material*			m_material;			// マテリアル情報へのポインタ

	Mesh();
	~Mesh();

	// モデルを描画する
	void DrawModel();
};

#endif // !_MESH_H_

