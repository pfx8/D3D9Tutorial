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

#include "Scene.h"

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	D3DXMATRIX		m_mtxWorld;	// ���[���h�}�g���b�N�X
	Camera*			m_camera;	// �J����
	Light*			m_light;	// ���C�g

	Plane*			m_FieldStone;	// �t�B�[���h
	Character*		m_woman;		// ��, �v���[���[

public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();

	void Scene00::UpdatePlayer(D3DXVECTOR3* Pos, D3DXVECTOR3* Speed);
};

#endif // !_SCENE00_H_

