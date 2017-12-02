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

public:
	D3DXMATRIX		m_mtxWorld;			// ���[���h�}�g���b�N�X
	ResourcesManager*	m_resourcesManager;	// ���\�[�X�}�l�W�����g

	Scene();
	~Scene();

	virtual void Update() {};
	virtual void Draw() {};

	// �t�@�C��(blender)����V���[�̎�����ǂݍ���
	HRESULT LoadSceneFile(std::string name);		// ������

	void SetSceneName(std::string name);		// �V�[���̖��O��ݒ�
	std::string GetSceneName();				// �V�[���̖��O���擾

	void ConsoleMessage(std::string sceneName);		// �R���\�[���ɕ\�����郁�b�Z�[�W
};

#endif // !_SCENE_H_

