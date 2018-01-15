//*****************************************************************************
//
// �G�l�~�[���� [Enemy.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <map>

#include "Engine.h"
#include "Bullet.h"
#include "DebugMessage.h"
#include "Modules\Character.h"
#include "Modules\BoundingBox.h"
#include "Modules\Model.h"
#include "Shader\CelShader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Enemy : public Character
{
private:

public:
	bool		m_isLife;	// �����t���O
	float	m_time;		// �^�C���`�F�b�N
	bool		m_isAttack;	// �U���t���O
	float	m_attackTime;	// �A���U���^�C��

	Enemy();
	~Enemy();

	void InitEnemy(D3DXVECTOR3 pos);	// �G�l�~�[���W��ݒ�
	void EnemyMove(D3DXVECTOR2 planeSize);	// �G�l�~�[�ړ�
	bool EnemyAttack(Character* player);	// �G�l�~�[�U��

	// �Վ�
	void Trans(float angle);
	bool CheckBB(Character* player);
};
#endif // !_ENEMY_H_

