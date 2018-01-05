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

#include "Modules/Scene.h"
#include "Modules/Character.h"
#include "Modules/Camera.h"
#include "Modules/Plane.h"
#include "Modules/Light.h"
#include "Modules/Shader.h"

#include "ResourcesManager.h"
#include "Engine.h"

#include "Shader/CelShader.h"

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
	Character*		m_hero;			// プレーヤー
	Character*		m_object;
	Character*		m_arrow;			// 方向矢印
	//Character*		m_ball;			// プレーヤー
	Light*			m_light;			// ライト

	bool				m_isGameStart;
public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();
	void Control();
	void SetRenderState();
};

#endif // !_SCENE00_H_

