//*****************************************************************************
//
// D3DTutorial���� [Scene00.h]
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
// �N���X�錾
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*			m_camera;	// �J����
	Shader*			m_shader;	// �V�F�[�_�[

	Plane*			m_fieldStone;	// �t�B�[���h
	Character*		m_hero;		// �v���[���[

public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();
	void Control();
};

#endif // !_SCENE00_H_

