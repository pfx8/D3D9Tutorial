//*****************************************************************************
//
// テクスチャ管理クラス [TextureManager.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef TEXTURE_MANAGER_CLASS_H_
#define TEXTURE_MANAGER_CLASS_H_

#include "Main.h"

// テクスチャマネジャー
class TextureManager
{
private:
	Texture m_Field_Grass;
	Texture m_Field_Stone;
	Texture m_Field_Checkered;

	Texture m_Null;

public:
	TextureManager();
	~TextureManager();

	void LoadTexture(Texture* texture);
	Texture* GetTexture(/*const char* Name*/int num = 99);
};

#endif // !TEXTURE_MANAGER_CLASS_H_

