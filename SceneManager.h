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
#include "Camera.h"
#include "Light.h"
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
	ResourcesManager*	m_resourcesManager;	// ���\�[�X�}�l�W�����g
	std::string		m_sceneName;			// �V���[�̖��O
	D3DXMATRIX		m_mtxWorld;			// ���[���h�}�g���b�N�X

	Camera*			m_camera;			// �J����
	Field*			m_FieldStone;		// �t�B�[���h
	Light*			m_light;			// ���C�g

	Character*		m_car1;	// ��, �v���[���[
	Character*		m_car2;	// ��,

	void ChangeRenderState();				// �����_�����O��ԍX�V
	void ConsoleMessage();					// �R���\�[���ɕ\�����郁�b�Z�[�W

public:
	SceneManager();
	~SceneManager();

	// �V���[��������(�Q�[���f�ނ�����������)
	void InitScene();

	// �V���[�̍X�V
	void Update();

	// �V���[�̏I������
	void UninitScene();

	// �V���[�̕`��
	void Draw();

	// �t�@�C��(blender)����V���[�̎�����ǂݍ���
	// ���̓��\�[�X���ׂĂ�ǂݍ���
	void LoadScene();	// �Վ�
	HRESULT LoadSceneFile(std::string name);		// ������

	// ���\�[�X�}�l�W�����g���擾
	ResourcesManager* GetResourcesManager();

	// �����_�����O��Ԃ�ݒ�
	void SetState();

	void UpdatePlayer();	// �v���[���[����X�V
}; 

#endif // !_SCENE_MANAGER_H_

