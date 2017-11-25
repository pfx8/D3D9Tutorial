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

#include "Scene00.h"
#include "Scene01.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneManager
{
private:
	Scene* m_scene;			// �V�[��
	//std::string m_sceneList[2];	// �V�[�����X�g

	void ChangeRenderState();	// �����_�����O��ԍX�V
	void ChooseScene();		// �V�[����I������
public:
	SceneManager();
	~SceneManager();

	void Update();		// �V�[���̍X�V
	void Draw();			// �V�[���̕`��
	void SetState();		// �����_�����O��Ԃ�ݒ�
}; 

#endif // !_SCENE_MANAGER_H_

