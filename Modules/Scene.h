//*****************************************************************************
//
// シーン処理 [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Engine.h"
#include "../ResourcesManager.h"
#include "../DebugMessage.h" 

#include <map>

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"


//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene
{
private:

public:
	D3DXMATRIX			m_worldMatrix;	// ワールドマトリックス
	ResourcesManager*		m_resourcesManager;	// リソースマネジメント
	DebugMessage*		m_message;		// メッセージ
	
	Scene();
	~Scene();

	virtual void Update() {};	// 仮想関数
	virtual void Draw() {};		// 仮想関数
	virtual void Control() {};	// プレーヤー操作関数

	// ファイル(blender)からシンーの資源を読み込み
	//HRESULT LoadSceneFile(std::string name);		// 未完成
};

#endif // !_SCENE_H_

