//*****************************************************************************
//
// メッシュクラス [MeshClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_CLASS_H_
#define _MESH_CLASS_H_

#include "Engine.h"

#include "MaterialClass.h"
#include "TextureManagerClass.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Mesh
{
private:
	LPD3DXMESH		m_mesh;				// メッシュ情報へのポインタ
	Material*		m_material;			// マテリアル情報へのポインタ

	TextureManager* m_textureManager;	// テクスチャマネジメント

	std::string		m_path;				// モデルのパス
public:
	Mesh();
	~Mesh();

	// 使いたいメッシュを読み込み
	void SetMesh(std::string path);

	// Xファイルを読み込む
	HRESULT ReadXFile();

	// モデルを描画する
	void DrawModel();
};

#endif // !_MESH_CLASS_H_

