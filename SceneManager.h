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
#include "Scene02.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneManager
{
private:
	Scene* m_scene;			// �V�[��

	void ChangeRenderState();	// �����_�����O��ԍX�V
	void ChooseScene();		// �V�[����I������
public:
	SceneManager();
	~SceneManager();

	void Update();		// �V�[���̍X�V
	void Draw();			// �V�[���̕`��
}; 

#endif // !_SCENE_MANAGER_H_

