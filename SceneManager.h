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
#include "SceneTitle.h"
#include "SceneEnding.h"

enum SCENESTATE
{
	SS_Title = 1,
	SS_Run,
	SS_Ending,
};

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneManager
{
private:
	SceneTitle*		m_sceneTitle;
	Scene00*		m_scene00;
	SceneEnding*	m_sceneEnding;
	SCENESTATE		m_sceneState;

	std::map <SCENESTATE, Scene*> m_sceneList;

	void ChangeRenderState();	// �����_�����O��ԍX�V
	void ChooseScene(SCENESTATE state);		// �V�[����I������
public:
	SceneManager();
	~SceneManager();

	void Update();		// �V�[���̍X�V
	void Draw();			// �V�[���̕`��
}; 

#endif // !_SCENE_MANAGER_H_

