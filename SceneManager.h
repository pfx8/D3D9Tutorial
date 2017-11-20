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
	ResourcesManager*	m_ResourcesManager;	// �e�N�X�`���}�l�W�����g
	std::string		m_Name;			// �V���[�̖��O

public:
	SceneManager();
	~SceneManager();
	
	// �e�N�X�`����ݒ�
	void SetTexture(Field* field, std::string name);
	void SetTexture(Character* character, std::string name);

	// �V���[�̏�����
	void InitScene();

	// �V���[�̍X�V
	void UpdateScene();

	// �V���[�̏I������
	void UninitScene();

	// �t�@�C������V���[�̎�����ǂݍ���
	// ���̓��\�[�X���ׂĂ�ǂݍ���
	void LoadScene();	// �Վ�
	HRESULT LoadSceneFile(std::string name);		// ������

	// �e�N�X�`���̃p�X��
};

#endif // !_SCENE_MANAGER_H_

