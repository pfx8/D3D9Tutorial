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
#include "Modules/Scene.h"
#include "Modules/Character.h"
#include "Modules/Camera.h"
#include "Modules/Plane.h"
#include "Modules/Light.h"
#include "Modules/Shader.h"
#include "Shader/CelShader.h"

#define ENEMY_SHIP_MAX 2
//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*			m_camera;		// カメラ
	CelShader*		m_celShader;		// トゥ―ンシェーダー
	Shader*			m_shader;		// ベーシックシェーダー
	Plane*			m_fieldStone;	// フィールド
	Character*		m_ship;			// プレーヤー
	Light*			m_light;			// ライト

	bool				m_isGameStart;
	Character*		m_enemyShip;		// 敵
public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();
	void Control();
	void SetRenderState();
};

#endif // !_SCENE00_H_

