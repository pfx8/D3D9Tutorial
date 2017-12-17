//*****************************************************************************
//
// D3DTutorial���� [Scene00.h]
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

#include "ResourcesManager.h"
#include "Shader.h"
#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*			m_camera;		// �J����
	Shader*			m_shader;		// �V�F�[�_�[
	Plane*			m_fieldStone;	// �t�B�[���h
	Character*		m_hero;			// �v���[���[
	Light*			m_light;			// ���C�g
public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();
	void Control();
	void SetRenderState();
};

#endif // !_SCENE00_H_

