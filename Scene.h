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
	ResourcesManager*	m_resourcesManager;	// リソースマネジメント
	std::string		m_sceneName;	// シンーの名前
	D3DXMATRIX		m_mtxWorld;	// ワールドマトリックス

	Camera*			m_camera;	// カメラ
	Light*			m_light;	// ライト

	// ゲーム素材
	Field*			m_FieldStone;	// フィールド
	Character*		m_car1;		// 車, プレーヤー
	Character*		m_car2;		// 車

public:
	Scene();
	~Scene();

	// シンーを初期化(ゲーム素材を初期化する)
	void InitScene(std::string name);

	// シンーの更新
	void Update();

	// シンーの描画
	void Draw();

	// リソースマネジメントを取得
	ResourcesManager* GetResourcesManager();

	// ファイル(blender)からシンーの資源を読み込み
	// 今はリソースすべてを読み込み
	void LoadScene();	// 臨時
	HRESULT LoadSceneFile(std::string name);		// 未完成

	void UpdatePlayer(D3DXVECTOR3* Pos, D3DXVECTOR3* Speed);	// プレーヤー操作更新
	std::string GetSceneName();	// シーんの名前を取得
};

#endif // !_SCENE_H_

