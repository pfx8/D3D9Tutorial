//*****************************************************************************
//
// Effect [Scene03.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE03_H_
#define _SCENE03_H_

#include "Engine.h"

#include <map>

#include "Scene.h"
#include "Camera.h"
#include "Shader.h"
#include "Plane.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene03 : public Scene
{
private:
	Camera*		m_camera;		// カメラ
	Shader*		m_shader;		// シェーダー
	Character*	m_woman;		// テストモデル
public:
	Scene03();
	~Scene03();

	void Update();
	void Draw();
};

#endif // !_SCENE03_H_

