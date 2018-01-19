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

#define FIRST_UP_SPEED	10.0f
#define MOVE_SPEED		1.0f
#define ACCELERARION		-0.2f
#define ONE_FRAME_TIME	(1.0f / 60.0f)
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
	bool m_isEnemyBullet;

	Bullet();
	~Bullet();

	void InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip);	// �G�l�~�[���W��ݒ�
	void BulletMove(D3DXVECTOR2 planeSize);	// �G�l�~�[�ړ�
	void CheckBulletAndShip();	// �G�l�~�[�U��
};
#endif // !_BULLET_H_

