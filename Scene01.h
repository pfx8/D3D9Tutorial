//*****************************************************************************
//
// ShaderTutorial処理 [Scene01.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE01_H_
#define _SCENE01_H_

#include "Engine.h"

#include <map>

#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Shader.h"
#include "Character.h"


//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene01 : public Scene
{
private:
	D3DXMATRIX	m_mtxWorld;	// ワールドマトリックス
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

