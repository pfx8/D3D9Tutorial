//*****************************************************************************
//
// テクスチャ管理クラス [TextureManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef TEXTURE_MANAGER_CLASS_H_
#define TEXTURE_MANAGER_CLASS_H_

#include "Main.h"

// テクスチャマネジャー
class TextureManager
{
private:
	Texture m_Field_Grass = { "Field_Grass", "data/TEXTURE/field000.jpg", NULL };
	Texture m_Field_Stone = { "Field_Stone", "data/TEXTURE/field001.jpg", NULL };
	Texture m_Field_Checkered = { "Field_Checkered", "data/TEXTURE/field002.jpg", NULL };
	Texture m_Null = { "Null", NULL, NULL };

public:
	TextureManager();
	~TextureManager();

	void LoadTexture(Texture* texture);
	Texture* GetTexture(/*const char* Name*/int num);
};

#endif // !TEXTURE_MANAGER_CLASS_H_

