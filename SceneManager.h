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
#include "SceneTitle.h"
#include "SceneEnding.h"

enum SCENESTATE
{
	SS_Title = 1,
	SS_Run,
	SS_Ending,
};

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneManager
{
private:
	SceneTitle*		sceneTitle;
	Scene00*		scene00;
	SceneEnding*	sceneEnding;
	SCENESTATE		sceneState;

	LPDIRECTSOUNDBUFFER8 bgm;

	std::map <SCENESTATE, Scene*> sceneList;

	void ChangeRenderState();	// レンダリング状態更新
	void ChooseScene(SCENESTATE state);		// シーンを選択する
public:
	SceneManager();
	~SceneManager();

	void Update();		// シーンの更新
	void Draw();			// シーンの描画
}; 

#endif // !_SCENE_MANAGER_H_

