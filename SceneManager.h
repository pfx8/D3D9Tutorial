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
#include "Camera.h"
#include "Light.h"
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
	ResourcesManager*	m_resourcesManager;	// リソースマネジメント
	std::string		m_sceneName;			// シンーの名前
	D3DXMATRIX		m_mtxWorld;			// ワールドマトリックス

	Camera*			m_camera;			// カメラ
	Field*			m_FieldStone;		// フィールド
	Light*			m_light;			// ライト

	Character*		m_car1;	// 車, プレーヤー
	Character*		m_car2;	// 車,

	void ChangeRenderState();				// レンダリング状態更新
	void ConsoleMessage();					// コンソールに表示するメッセージ

public:
	SceneManager();
	~SceneManager();

	// シンーを初期化(ゲーム素材を初期化する)
	void InitScene();

	// シンーの更新
	void Update();

	// シンーの終了処理
	void UninitScene();

	// シンーの描画
	void Draw();

	// ファイル(blender)からシンーの資源を読み込み
	// 今はリソースすべてを読み込み
	void LoadScene();	// 臨時
	HRESULT LoadSceneFile(std::string name);		// 未完成

	// リソースマネジメントを取得
	ResourcesManager* GetResourcesManager();

	// レンダリング状態を設定
	void SetState();

	void UpdatePlayer();	// プレーヤー操作更新
}; 

#endif // !_SCENE_MANAGER_H_

