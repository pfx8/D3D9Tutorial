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
// �N���X�錾
//
//*****************************************************************************
class Scene01 : public Scene
{
private:
	Camera*		m_camera;		// �J����
	Shader*		m_shader;		// �V�F�[�_�[
	Character*	m_dolphin;	// �C���J
	Character*	m_dolphin2;	// �C���J
public:
	Scene01();
	~Scene01();

	void Update();
	void Draw();
};

#endif // !_SCENE01_H_

