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
	// 検索マッピングを作る
	m_TextureList[m_FieldGrass.Name] = m_FieldGrass;
	m_TextureList[m_FieldStone.Name] = m_FieldStone;
	m_TextureList[m_FieldCheckered.Name] = m_FieldCheckered;
	m_TextureList[m_Null.Name] = m_Null;
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
LPDIRECT3DTEXTURE9* ResourcesManager::LoadTexture(std::string name)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TextureStruct* texture = GetTextureStruct(name);	// ロードしたいテクスチャ構造体を取得

	if (texture->Path != NULL)
	{

		// テクスチャを読み込み
		std::cout << "Loading Texture:" << texture->Path;	// コンソールにメッセージを出す
		if (FAILED(D3DXCreateTextureFromFile(pDevice, texture->Path, &texture->TexturePoint)))
		{
			std::cout << " Failed!" << std::endl;	// コンソールにメッセージを出す
			return NULL;
		}
		else
		{
			std::cout << " OK!" << std::endl;	// コンソールにメッセージを出す
			return &texture->TexturePoint;
		}
	}
	else
	{
		return &texture->TexturePoint;
	}
}


//*****************************************************************************
//
// テクスチャ構造体を取得
//
//*****************************************************************************
TextureStruct* ResourcesManager::GetTextureStruct(std::string name)
{
	if(m_TextureList.find(name) != m_TextureList.end())
	{
		return &m_TextureList[name];
	}

	return NULL;
}