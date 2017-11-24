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

#include "Scene.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneManager
{
private:
	Scene*	m_sceneD3D;		// �V�[��
	void ConsoleMessage();		// �R���\�[���ɕ\�����郁�b�Z�[�W
	void ChangeRenderState();	// �����_�����O��ԍX�V

public:
	SceneManager();
	~SceneManager();

	void InitScene();		// �V���[��������(�Q�[���f�ނ�����������)
	void Update();		// �V�[���̍X�V
	void Draw();			// �V���[�̕`��
	void SetState();		// �����_�����O��Ԃ�ݒ�
}; 

#endif // !_SCENE_MANAGER_H_

