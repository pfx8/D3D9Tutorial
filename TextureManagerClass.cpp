//*****************************************************************************
//
// テクスチャ管理クラス [TextureManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "TextureManagerClass.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
TextureManager::TextureManager()
{
	LoadTexture(&m_Field_Grass);
	LoadTexture(&m_Field_Stone);
	LoadTexture(&m_Field_Checkered);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
TextureManager::~TextureManager()
{

}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
void TextureManager::LoadTexture(Texture* texture)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, texture->Path, &texture->TexturePoint);
}

//*****************************************************************************
//
// テクスチャを取得
//
//*****************************************************************************
Texture* TextureManager::GetTexture(/*const char* Name*/int num)
{
	switch (num)
	{
	case 0:return &m_Field_Grass;
	case 1:return &m_Field_Stone;
	case 2:return &m_Field_Checkered;
	case 3:return &m_Null;
	default:
		break;
	}

	return NULL;
}