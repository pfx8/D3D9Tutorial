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

#include "Scene00.h"
#include "Scene01.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneManager
{
private:
	Scene* m_scene;			// シーン
	//std::string m_sceneList[2];	// シーンリスト

	void ChangeRenderState();	// レンダリング状態更新
	void ChooseScene();		// シーンを選択する
public:
	SceneManager();
	~SceneManager();

	void Update();		// シーンの更新
	void Draw();			// シーンの描画
	void SetState();		// レンダリング状態を設定
}; 

#endif // !_SCENE_MANAGER_H_

