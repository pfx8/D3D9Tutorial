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
	m_textureList["fieldGrass"] = "data/TEXTURE/field000.jpg";
	m_textureList["fieldStone"] = "data/TEXTURE/field001.jpg";
	m_textureList["fieldCheckered"] = "data/TEXTURE/field002.jpg";
	m_textureList["1032"] = "data/TEXTURE/1032.jpg";
	m_textureList["1033"] = "data/TEXTURE/1033.jpg";
	m_textureList["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	m_meshList["car1"] = "data/MODEL/car001.x";
	m_meshList["car2"] = "data/MODEL/car002.x";
	m_meshList["dolphin1"] = "data/MODEL/Dolphin1.x";
	m_meshList["dolphin2"] = "data/MODEL/Dolphin3.x";
	m_meshList["woman"] = "data/MODEL/woman.x";
	m_meshList["rockman"] = "data/MODEL/rockman.x";
	m_meshList["test"] = "data/MODEL/test.x";
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
			std::cout << "[Error] Loading Texture:" << name << " Failed!" << std::endl;	// コンソールにメッセージを出す
			return E_FAIL;
		}
		else
		{
			std::cout << "[Information] Loading Texture:" << name << " OK!" << std::endl;	// コンソールにメッセージを出す
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
	if(m_textureList.find(name) != m_textureList.end())
	{
		return m_textureList[name];
	}
}

//*****************************************************************************
//
// メッシュを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadMesh(std::string name, Model* model)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(D3DXLoadMeshFromX(			// Xファイルの読み込み
		GetMeshPath(name).data(),			// モデルのファイル名
		D3DXMESH_SYSTEMMEM,					// メッシュのメモリ確保オプション
		pDevice,							// デバイスへのポインタ
		NULL,								// 隣接性データを含むバッファへのポインタ
		&model->m_material->m_materialBuffer,// マテリアルデータを含むバッファへのポインタ
		NULL,								// エフェクトインスタンスを含むバッファへのポインタ
		&model->m_material->m_materialNum,	// マテリアル構造体の数
		&model->m_meshPoint)))				// メッシュへのポインタ
	{
		std::cout << "[Error] Loading Model:" << name << " Failed!" << std::endl;
		return E_FAIL;
	}
	else
	{
		std::cout << "[Information] Loading Model:" << name << " OK!" << std::endl;
	}

	model->m_material->m_materialPoint = new D3DMATERIAL9[model->m_material->m_materialNum];	// マテリアルの数によってマテリアルを格納できるメモリを確保
	model->m_meshTexturePoint = new LPDIRECT3DTEXTURE9[model->m_material->m_materialNum];		// マテリアルの数によってテクスチャを格納できるメモリを確保

	D3DXMATERIAL* materials = (D3DXMATERIAL*)model->m_material->m_materialBuffer->GetBufferPointer();	// Xファイルに保存されているマテリアル情報構造体
	for (DWORD count = 0; count < model->m_material->m_materialNum; count++)
	{
		model->m_material->m_materialPoint[count] = materials[count].MatD3D; // マテリアルのプロパティをコピー
		model->m_material->m_materialPoint[count].Ambient = model->m_material->m_materialPoint[count].Diffuse;	// アンビエント色をディフューズ色にする

		// Xファイルの情報によってすべてのテクスチャを読み込み
		if (materials[count].pTextureFilename == NULL)
		{
			model->m_meshTexturePoint[count] = NULL;	// テクスチャ無し
		}
		else
		{
			if (FAILED(D3DXCreateTextureFromFile(pDevice, materials[count].pTextureFilename, &model->m_meshTexturePoint[count])))
			{
				std::cout << "[Error] Material's texture load Fail!" << std::endl;
				return E_FAIL;
			}
		}
	}

	// ッシュの面および頂点の順番変更を制御し、パフォーマンスを最適化する
	model->m_meshPoint->OptimizeInplace(D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL);

	return S_OK;
}

//*****************************************************************************
//
// メッシュパスを取得
//
//*****************************************************************************
std::string ResourcesManager::GetMeshPath(std::string name)
{
	if (m_meshList.find(name) != m_meshList.end())
	{
		return m_meshList[name];
	}

	return NULL;
}