//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "Engine.h"

#include <map>

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ResourcesManager
{
private:
	TextureStruct m_FieldGrass = { "FieldGrass", "data/TEXTURE/field000.jpg", NULL };
	TextureStruct m_FieldStone = { "FieldStone", "data/TEXTURE/field001.jpg", NULL };
	TextureStruct m_FieldCheckered = { "FieldCheckered", "data/TEXTURE/field002.jpg", NULL};

	TextureStruct m_Null = { "NULL", NULL, NULL };

	std::map < std::string, TextureStruct> m_TextureList;	// テクスチャリスト
	TextureStruct* GetTextureStruct(std::string name);	// テクスチャを取得
public:
	ResourcesManager();
	~ResourcesManager();

	LPDIRECT3DTEXTURE9	* LoadTexture(std::string name);	// テクスチャを読み込み
	void LoadMesh(std::string name);	// メッシュを読み込み

};

#endif // !_RESOURCES_MANAGER_H_

