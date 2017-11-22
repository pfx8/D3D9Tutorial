//*****************************************************************************
//
// �V�[���}�l�W���[���� [SceneManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Engine.h"

#include <map>

#include "Character.h"
#include "Field.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// �V���[�\����
//
//*****************************************************************************

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneManager
{
private:
	ResourcesManager*	m_ResourcesManager;	// ���\�[�X�}�l�W�����g
	std::string		m_SceneName;			// �V���[�̖��O

public:
	SceneManager();
	~SceneManager();

	// �V���[��������
	void InitScene();

	// �V���[�̍X�V
	void UpdateScene();

	// �V���[�̏I������
	void UninitScene();

	// �t�@�C��(blender)����V���[�̎�����ǂݍ���
	// ���̓��\�[�X���ׂĂ�ǂݍ���
	void LoadScene();	// �Վ�
	HRESULT LoadSceneFile(std::string name);		// ������

	// ���\�[�X�}�l�W�����g���擾
	ResourcesManager* GetResourcesManager();
}; 

#endif // !_SCENE_MANAGER_H_

