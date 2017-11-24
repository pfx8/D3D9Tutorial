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
	ResourcesManager*	m_resourcesManager;	// リソースマネジメント

public:
	D3DXMATRIX		m_mtxWorld;			// ワールドマトリックス

	Scene();
	~Scene();

	virtual void Update() {};
	virtual void Draw() {};

	// ファイル(blender)からシンーの資源を読み込み
	HRESULT LoadSceneFile(std::string name);		// 未完成

	ResourcesManager* GetResourcesManager();	//リソースマネジメントを取得
	void SetSceneName(std::string name);	// シーンの名前を設定
	std::string GetSceneName();	// シーンの名前を設定
};

#endif // !_SCENE_H_

