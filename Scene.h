//*****************************************************************************
//
// �V�[������ [Scene.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_H_
#define _SCENE_H_

#include "Engine.h"

#include <map>

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Field.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene
{
private:
	std::string		m_sceneName;	// �V���[�̖��O
	ResourcesManager*	m_resourcesManager;	// ���\�[�X�}�l�W�����g

public:
	D3DXMATRIX		m_mtxWorld;			// ���[���h�}�g���b�N�X

	Scene();
	~Scene();

	virtual void Update() {};
	virtual void Draw() {};

	// �t�@�C��(blender)����V���[�̎�����ǂݍ���
	HRESULT LoadSceneFile(std::string name);		// ������

	ResourcesManager* GetResourcesManager();	//���\�[�X�}�l�W�����g���擾
	void SetSceneName(std::string name);	// �V�[���̖��O��ݒ�
	std::string GetSceneName();	// �V�[���̖��O��ݒ�
};

#endif // !_SCENE_H_

