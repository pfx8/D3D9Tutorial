//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "../Engine.h"
#include "../ResourcesManager.h"
#include "../DebugMessage.h" 

#include <map>

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"


//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene
{
private:

public:
	D3DXMATRIX			m_worldMatrix;	// ���[���h�}�g���b�N�X
	ResourcesManager*		m_resourcesManager;	// ���\�[�X�}�l�W�����g
	DebugMessage*		m_message;		// ���b�Z�[�W
	
	Scene();
	~Scene();

	virtual void Update() {};	// ���z�֐�
	virtual void Draw() {};		// ���z�֐�
	virtual void Control() {};	// �v���[���[����֐�

	// �t�@�C��(blender)����V���[�̎�����ǂݍ���
	//HRESULT LoadSceneFile(std::string name);		// ������
};

#endif // !_SCENE_H_

