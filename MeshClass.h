//*****************************************************************************
//
// メッシュクラス [MeshClass.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _MESH_CLASS_H_
#define _MESH_CLASS_H_

#include "Main.h"

#include "MaterialClass.h"
#include "TextureManagerClass.h"

class Mesh
{
private:
	LPD3DXMESH		m_mesh;		// メッシュ情報へのポインタ
	Material*		m_material; // マテリアル情報へのポインタ

	TextureManager* m_textureManager; // テクスチャマネジメント

public:
	Mesh();
	~Mesh();

	// Xファイルを読み込む
	HRESULT ReadXFile();

	// モデルを描画する
	void DrawModel();
};

#endif // !_MESH_CLASS_H_

