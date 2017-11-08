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


	// 臨時
	//LPD3DXBUFFER		m_D3DXBuffMatModel = NULL;	// マテリアル情報へのポインタ
	//DWORD				m_NumMatModel = NULL;		// マテリアル情報の数
	//LPDIRECT3DTEXTURE9	m_TexturePoint = NULL;
public:
	Mesh();
	~Mesh();

	// Xファイルを読み込む
	HRESULT ReadXFile();

	// モデルを描画する
	void DrawModel();
};

#endif // !_MESH_CLASS_H_

