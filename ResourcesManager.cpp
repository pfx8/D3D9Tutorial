//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ResourcesManager.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ResourcesManager::ResourcesManager()
{
	// テクスチャ検索マッピングを作る
	m_TextureList["FieldGrass"] = "data/TEXTURE/field000.jpg";
	m_TextureList["FieldStone"] = "data/TEXTURE/field001.jpg";
	m_TextureList["FieldCheckered"] = "data/TEXTURE/field002.jpg";
	m_TextureList["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	m_MeshList["Car1"] = "data/MODEL/car001.x";
	m_MeshList["Car2"] = "data/MODEL/car002.x";
	m_MeshList["Dolphin1"] = "data/MODEL/Dolphin1.x";
	m_MeshList["Dolphin2"] = "data/MODEL/Dolphin2.x";
	m_MeshList["Woman"] = "data/MODEL/Woman.x";
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ResourcesManager::~ResourcesManager()
{

}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetTextureStruct(name).data() != "NULL")
	{
		// テクスチャを読み込み
		std::cout << "Loading Texture:" << name;	// コンソールにメッセージを出す
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice, 
			GetTextureStruct(name).data(),
			texturePoint)))
		{
			std::cout << " Failed!" << std::endl;	// コンソールにメッセージを出す
			return E_FAIL;
		}
		else
		{
			std::cout << " OK!" << std::endl;	// コンソールにメッセージを出す
			return S_OK;
		}
	}
	else
	{
		*texturePoint = NULL;
		return S_OK;
	}
}


//*****************************************************************************
//
// テクスチャ構造体を取得
//
//*****************************************************************************
std::string ResourcesManager::GetTextureStruct(std::string name)
{
	if(m_TextureList.find(name) != m_TextureList.end())
	{
		return m_TextureList[name];
	}
}

//*****************************************************************************
//
// メッシュを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadMesh(std::string name, Mesh* mesh)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(
		GetMeshPath(name).data(),			// モデルのファイル名
		D3DXMESH_SYSTEMMEM,				// メッシュのメモリ確保オプション
		pDevice,							// デバイスへのポインタ
		NULL,							// 隣接性データを含むバッファへのポインタ
		mesh->m_material->GetMaterialPoint(),
		NULL,							// エフェクトインスタンスを含むバッファへのポインタ
		mesh->m_material->GetMterialNumber(),
		&mesh->m_mesh)))						// メッシュへのポインタ
	{
		return E_FAIL;
	}

	return S_OK;
}

//*****************************************************************************
//
// メッシュパスを取得
//
//*****************************************************************************
std::string ResourcesManager::GetMeshPath(std::string name)
{
	if (m_MeshList.find(name) != m_MeshList.end())
	{
		return m_MeshList[name];
	}

	return NULL;
}