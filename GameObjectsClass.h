//=============================================================================
//
// �Q�[�����������N���X [GameObjectsClass.h]
// Author : �����E�@�J���V��
//
//=============================================================================
#ifndef _GAMEOBEJCTS_CLASS_H_
#define _GAMEOBJECTS_CLASS_H_

#include "Main.h"

class GameObjectsClass
{
private:
	bool m_Status;

	void InitEMVer(void);
	void InitEMLig(void);
public:
	GameObjectsClass();					// �R���X�g���N�^
	~GameObjectsClass();					// �f�X�g���N�^

	void SetExample(ExampleType mode);
	bool GetStatus();

};

#endif // !_GAMEOBEJCTS_CLASS_H_
