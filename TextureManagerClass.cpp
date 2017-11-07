//*****************************************************************************
//
// テクスチャ管理クラス [TextureManager.cpp]
//
// Author : リョウ　カンシン
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
	Texture m_Field_Grass     = { "Field_Grass", "data/TEXTURE/field000.jpg", NULL };
	Texture m_Field_Stone     = { "Field_Stone", "data/TEXTURE/field001.jpg", NULL };
	Texture m_Field_Checkered = { "Field_Checkered", "data/TEXTURE/field002.jpg", NULL };
	Texture m_Null            = { "Null", NULL, NULL};

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

	if (texture->TexturePoint != NULL)
	{
		std::cout << "Load " << texture->Name << " Successed！" << std::endl;
	}
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
	default:
		break;
	}

	return &m_Null;;
}