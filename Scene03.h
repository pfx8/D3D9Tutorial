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
// �N���X�錾
//
//*****************************************************************************
class Scene03 : public Scene
{
private:
	Camera*		m_camera;		// �J����
	Shader*		m_shader;		// �V�F�[�_�[
	Character*	m_woman;		// �e�X�g���f��
public:
	Scene03();
	~Scene03();

	void Update();
	void Draw();
};

#endif // !_SCENE03_H_

