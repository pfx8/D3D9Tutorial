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
#include "Modules\Camera.h"

#define FIRST_UP_SPEED	10.0f
#define MOVE_SPEED		0.57f
#define ACCELERARION	-0.2f

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Bullet : public Character
{
private:
	float	speed;	// �ŏ��̃X�s�[�h

public:
	bool	isUse;		// �g���Ă邩�ǂ����𔻒f����
	bool	isEnemyBullet;
	Model*	model;		// ���f��

	Bullet();
	~Bullet();

	void InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip);	// �G�l�~�[���W��ݒ�
	void BulletMove(D3DXVECTOR2 planeSize);	// �G�l�~�[�ړ�
	void CheckBulletAndShip();	// �G�l�~�[�U��

	void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);
};
#endif // !_BULLET_H_

