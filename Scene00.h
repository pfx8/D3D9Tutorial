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
#include "Modules/Shader.h"

#include "ResourcesManager.h"
#include "Engine.h"

#include "Shader/CelShader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*			m_camera;		// �J����
	CelShader*		m_celShader;		// �g�D�\���V�F�[�_�[
	Shader*			m_shader;		// �x�[�V�b�N�V�F�[�_�[
	Plane*			m_fieldStone;	// �t�B�[���h
	Character*		m_hero;			// �v���[���[
	Character*		m_object;
	Character*		m_arrow;			// �������
	//Character*		m_ball;			// �v���[���[
	Light*			m_light;			// ���C�g

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

