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
	LPD3DXMESH			m_meshPoint;			// メッシュ情報へのポインタ
	LPDIRECT3DTEXTURE9*	m_meshTexturePoint;	// テクスチャマネジメント
	Material*				m_material;			// マテリアル情報へのポインタ

	Mesh();
	~Mesh();

	void DrawModel();	// モデルを描画する
	void DrawModel(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl);	// モデルを描画する(Shader)
};

#endif // !_MESH_H_

