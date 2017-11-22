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
// テクスチャリストを初期化する
//
//*****************************************************************************
void ResourcesManager::InitTextureList()
{
	// コンソールにメッセージを出す
	std::cout << "Loading Texture:" << std::endl;

	// テクスチャを読み込み
	LoadTexture(&m_FieldGrass);
	LoadTexture(&m_FieldStone);
	LoadTexture(&m_FieldCheckered);

	// 検索マッピングを作る
	m_TextureList[m_FieldGrass.Name]	= m_FieldGrass.TexturePoint;
	m_TextureList[m_FieldStone.Name]	= m_FieldStone.TexturePoint;
	m_TextureList[m_FieldCheckered.Name]	= m_FieldCheckered.TexturePoint;
	m_TextureList[m_Null.Name]			= m_Null.TexturePoint;
}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadTexture(TextureStruct* texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, texture->Path, &texture->TexturePoint)))
	{
		return E_FAIL;
	}

	// コンソールにメッセージを出す
	std::cout << texture->Path << " OK!" << std::endl;

	return S_OK;
}

//*****************************************************************************
//
// テクスチャを取得
//
//*****************************************************************************
LPDIRECT3DTEXTURE9* ResourcesManager::SetTexture(std::string name)
{
	if(m_TextureList.find(name) != m_TextureList.end())
	{
		return &m_TextureList[name];
	}

	return NULL;
}