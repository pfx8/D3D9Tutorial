//*****************************************************************************
//
// �e���� [Bullet.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

#include <map>

#include "Engine.h"
#include "Modules\Character.h"

#define FIRST_SPEED 7.0f
#define ACCELERARION	-0.05f
#define ONE_FRAME_TIME (1.0f / 60.0f)
//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Bullet : public Character
{
private:
	float m_upSpeed;	// �ŏ��̃X�s�[�h

public:
	bool m_isUse;	// �g���Ă邩�ǂ����𔻒f����

	Bullet();
	~Bullet();

	void InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector);	// �G�l�~�[���W��ݒ�
	void BulletMove();	// �G�l�~�[�ړ�
	void CheckBulletAndShip();	// �G�l�~�[�U��
};
#endif // !_BULLET_H_

