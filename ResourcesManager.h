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
	Texture m_FieldGrass = { "FieldGrass", "data/TEXTURE/field000.jpg", NULL };
	Texture m_FieldStone = { "FieldStone", "data/TEXTURE/field001.jpg", NULL };
	Texture m_FieldCheckered = { "FieldCheckered", "data/TEXTURE/field002.jpg", NULL};
	Texture m_Null = { "Null", NULL, NULL };

	// テクスチャリスト
	std::map < std::string, LPDIRECT3DTEXTURE9> m_TextureList;

	// テクスチャを読み込み
	HRESULT LoadTexture(Texture* texture);

public:
	ResourcesManager();
	~ResourcesManager();

	// テクスチャリストを初期化する
	void InitTextureList();

	// テクスチャを取得
	LPDIRECT3DTEXTURE9* GetTexture(std::string name);
};

#endif // !_RESOURCES_MANAGER_H_

