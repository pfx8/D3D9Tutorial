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

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneManager
{
private:
	Scene*	m_sceneD3D;		// シーン

	void ChangeRenderState();	// レンダリング状態更新
	
public:
	SceneManager();
	~SceneManager();

	void Update();		// シーンの更新
	void Draw();			// シンーの描画
	void SetState();		// レンダリング状態を設定
}; 

#endif // !_SCENE_MANAGER_H_

