//*****************************************************************************
//
// シーンマネジャー処理 [SceneManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Engine.h"

#include <map>

#include "Character.h"
#include "Field.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// シンー構造体
//
//*****************************************************************************

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneManager
{
private:
	ResourcesManager*	m_ResourcesManager;	// テクスチャマネジメント
	std::string		m_Name;			// シンーの名前

public:
	SceneManager();
	~SceneManager();
	
	// テクスチャを設定
	void SetTexture(Field* field, std::string name);
	void SetTexture(Character* character, std::string name);

	// シンーの初期化
	void InitScene();

	// シンーの更新
	void UpdateScene();

	// シンーの終了処理
	void UninitScene();

	// ファイルからシンーの資源を読み込み
	// 今はリソースすべてを読み込み
	void LoadScene();	// 臨時
	HRESULT LoadSceneFile(std::string name);		// 未完成

	// テクスチャのパスを
};

#endif // !_SCENE_MANAGER_H_

