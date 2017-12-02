//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "Engine.h"

#include <map>

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Field.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:
	std::string		m_sceneName;	// シンーの名前

public:
	D3DXMATRIX		m_mtxWorld;			// ワールドマトリックス
	ResourcesManager*	m_resourcesManager;	// リソースマネジメント

	Scene();
	~Scene();

	virtual void Update() {};
	virtual void Draw() {};

	// ファイル(blender)からシンーの資源を読み込み
	HRESULT LoadSceneFile(std::string name);		// 未完成

	void SetSceneName(std::string name);		// シーンの名前を設定
	std::string GetSceneName();				// シーンの名前を取得

	void ConsoleMessage(std::string sceneName);		// コンソールに表示するメッセージ
};

#endif // !_SCENE_H_

