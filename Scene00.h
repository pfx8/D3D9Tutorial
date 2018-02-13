//*****************************************************************************
//
// D3DTutorial処理 [Scene00.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE00_H_
#define _SCENE00_H_

#include <map>

#include "ResourcesManager.h"
#include "Engine.h"
#include "Enemy.h"
#include "Bullet.h"

#include "Modules\Scene.h"
#include "Modules\Character.h"
#include "Modules\BoundingBox.h"
#include "Modules\Camera.h"
#include "Modules\Plane.h"
#include "Modules\Light.h"
#include "Modules\Shader.h"
#include "Modules\SkyBox.h"
#include "Modules\ScreenPolygon.h"

#include "Shader\RHWShader.h"
#include "Shader\CelShader.h"
#include "Shader\ShadowMapShader.h"

#define ENEMY_MAX 5
#define BULLET_MAX 21

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*				camera;		// カメラ
	CelShader*			celShader;	// トゥ―ンシェーダー

	Shader*				shader;		// ベーシックシェーダー
	Plane*				sea;			// フィールド海
	Light*				directionLight;		// ライト
	Enemy*				enemyShip;	// 敵
	Bullet*				bullet;		// 弾
	SkyBox*				skyBox;		// スカイボックス
	ShadowMapShader*	shadowMap;	// シャドーマップ
	ScreenPolygon*		screenPolygon;// RHWポリゴン

	
public:
	Character*			ship;			// プレーヤー

	Scene00();
	~Scene00();

	void InitScene00();		// 初期化
	void Update();			// 更新
	void Draw();			// 描画
	void Control();			// 操作関数
	void SetRenderState();	// レンダリングを設定

	bool CheckBB(Bullet* bullet, Enemy* enemy);		// 当たり判定(長方形)
	bool CheckBC(Bullet* bullet, Enemy* enemy);		// 当たり判定(円)
};

#endif // !_SCENE00_H_

