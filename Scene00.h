//*****************************************************************************
//
// D3DTutorial処理 [Scene00.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE00_H_
#define _SCENE00_H_

#include "Engine.h"

#include <map>

#include "Modules/Scene.h"
#include "Modules/Character.h"
#include "Modules/Camera.h"
#include "Modules/Plane.h"
#include "ResourcesManager.h"
#include "Shader.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*			m_camera;	// カメラ
	Shader*			m_shader;	// シェーダー

	Plane*			m_fieldStone;	// フィールド
	Character*		m_hero;		// プレーヤー

public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();
	void Control();
};

#endif // !_SCENE00_H_

