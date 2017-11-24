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
	ResourcesManager*	m_resourcesManager;	// ���\�[�X�}�l�W�����g
	std::string		m_sceneName;	// �V���[�̖��O
	D3DXMATRIX		m_mtxWorld;	// ���[���h�}�g���b�N�X

	Camera*			m_camera;	// �J����
	Light*			m_light;	// ���C�g

	// �Q�[���f��
	Field*			m_FieldStone;	// �t�B�[���h
	Character*		m_car1;		// ��, �v���[���[
	Character*		m_car2;		// ��

public:
	Scene();
	~Scene();

	// �V���[��������(�Q�[���f�ނ�����������)
	void InitScene(std::string name);

	// �V���[�̍X�V
	void Update();

	// �V���[�̕`��
	void Draw();

	// ���\�[�X�}�l�W�����g���擾
	ResourcesManager* GetResourcesManager();

	// �t�@�C��(blender)����V���[�̎�����ǂݍ���
	// ���̓��\�[�X���ׂĂ�ǂݍ���
	void LoadScene();	// �Վ�
	HRESULT LoadSceneFile(std::string name);		// ������

	void UpdatePlayer(D3DXVECTOR3* Pos, D3DXVECTOR3* Speed);	// �v���[���[����X�V
	std::string GetSceneName();	// �V�[��̖��O���擾
};

#endif // !_SCENE_H_

