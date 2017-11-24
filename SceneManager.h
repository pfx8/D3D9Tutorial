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

#include "Scene.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneManager
{
private:
	Scene*	m_sceneD3D;		// シーン
	void ConsoleMessage();		// コンソールに表示するメッセージ
	void ChangeRenderState();	// レンダリング状態更新

public:
	SceneManager();
	~SceneManager();

	void InitScene();		// シンーを初期化(ゲーム素材を初期化する)
	void Update();		// シーンの更新
	void Draw();			// シンーの描画
	void SetState();		// レンダリング状態を設定
}; 

#endif // !_SCENE_MANAGER_H_

