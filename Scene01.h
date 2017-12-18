//*****************************************************************************
//
// VertexShader [Scene01.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE01_H_
#define _SCENE01_H_

#include "Engine.h"
#include "Modules\Shader.h"

#include <map>

#include "Modules/Scene.h"
#include "Modules/Camera.h"
#include "Modules/Light.h"
#include "Modules/Character.h"


//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene01 : public Scene
{
private:
	Camera*		m_camera;		// カメラ
	Shader*		m_shader;		// シェーダー
	Character*	m_dolphin;	// イルカ
	Character*	m_dolphin2;	// イルカ
public:
	Scene01();
	~Scene01();

	void Update();
	void Draw();
};

#endif // !_SCENE01_H_

