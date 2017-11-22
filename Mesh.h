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
	LPD3DXMESH		m_mesh;		// メッシュ情報へのポインタ
	Material*			m_material;	// マテリアル情報へのポインタ
	std::string		m_path;		// モデルのパス

	PDIRECT3DTEXTURE9	m_MeshTexturePoint;		// テクスチャマネジメント

public:
	Mesh();
	~Mesh();

	// 使いたいメッシュを読み込み
	void SetMesh(std::string path);

	// Xファイルを読み込む
	HRESULT ReadXFile();

	// モデルを描画する
	void DrawModel();

	// メッシュにテクスチャを設定する
	void SetMeshTexture(PDIRECT3DTEXTURE9* texturePoint);
};

#endif // !_MESH_H_

