//=============================================================================
//
// �Q�[�����������N���X [GameObjects.h]
// Author : �����E�@�J���V��
//
//=============================================================================
#ifndef _GAMEOBEJCTS_H_
#define _GAMEOBJECTS_H

#include "Main.h"

class GameObjects
{
private:
	bool m_Status;

	void InitEMVer(void);
	void InitEMLig(void);
public:
	GameObjects();					// �R���X�g���N�^
	~GameObjects();					// �f�X�g���N�^

	void SetExample(ExampleType mode);
	bool GetStatus();

};

#endif // !_GAMEOBEJCTS_H_
