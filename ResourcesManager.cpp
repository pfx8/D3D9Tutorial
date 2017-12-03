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
	m_TextureList["fieldGrass"] = "data/TEXTURE/field000.jpg";
	m_TextureList["fieldStone"] = "data/TEXTURE/field001.jpg";
	m_TextureList["fieldCheckered"] = "data/TEXTURE/field002.jpg";
	m_TextureList["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	m_MeshList["car1"] = "data/MODEL/car001.x";
	m_MeshList["car2"] = "data/MODEL/car002.x";
	m_MeshList["dolphin1"] = "data/MODEL/Dolphin1.x";
	m_MeshList["dolphin2"] = "data/MODEL/Dolphin3.x";
	m_MeshList["woman"] = "data/MODEL/Woman.x";
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
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice, 
			GetTextureStruct(name).data(),
			texturePoint)))
		{
			std::cout << "Loading Texture:" << name << " Failed!" << std::endl;	// コンソールにメッセージを出す
			return E_FAIL;
		}
		else
		{
			std::cout << "Loading Texture:" << name << " OK!" << std::endl;	// コンソールにメッセージを出す
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

	LPD3DXBUFFER materialBuffer;	// マテリアルバッファ
	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(
		GetMeshPath(name).data(),			// モデルのファイル名
		D3DXMESH_SYSTEMMEM,				// メッシュのメモリ確保オプション
		pDevice,							// デバイスへのポインタ
		NULL,							// 隣接性データを含むバッファへのポインタ
		&materialBuffer,					// マテリアルデータを含むバッファへのポインタ
		NULL,							// エフェクトインスタンスを含むバッファへのポインタ
		&mesh->m_material->m_materialNum,	// マテリアル構造体の数
		&mesh->m_meshPoint)))				// メッシュへのポインタ
	{
		std::cout << "Loading Mesh:" << name << " Failed!" << std::endl;
		return E_FAIL;
	}
	else
	{
		std::cout << "Loading Mesh:" << name << " OK!" << std::endl;
	}

	mesh->m_material->m_materialPoint = new D3DMATERIAL9[mesh->m_material->m_materialNum];	// マテリアルの数によってマテリアルを格納できるメモリを確保
	mesh->m_meshTexturePoint = new LPDIRECT3DTEXTURE9[mesh->m_material->m_materialNum];	// マテリアルの数によってテクスチャを格納できるメモリを確保

	D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();	// Xファイルに保存されているマテリアル情報構造体

	for (DWORD count = 0; count < mesh->m_material->m_materialNum; count++)
	{
		mesh->m_material->m_materialPoint[count] = materials[count].MatD3D; // マテリアルのプロパティをコピー
		mesh->m_material->m_materialPoint[count].Ambient = mesh->m_material->m_materialPoint[count].Diffuse;	// アンビエント色をディフューズ色にする

		// Xファイルの情報によってすべてのテクスチャを読み込み
		if (FAILED(D3DXCreateTextureFromFile(pDevice, materials[count].pTextureFilename, &mesh->m_meshTexturePoint[count])))
		{
			std::cout << "Material's texture read FAIL" << std::endl;
			return E_FAIL;
		}
	}

	// ッシュの面および頂点の順番変更を制御し、パフォーマンスを最適化する
	mesh->m_meshPoint->OptimizeInplace(D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL);

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