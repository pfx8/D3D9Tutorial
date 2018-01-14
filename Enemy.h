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
	Enemy();
	~Enemy();

	void InitEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 direction);	// �G�l�~�[���W��ݒ�
	void EnemyMove();	// �G�l�~�[�ړ�
	void EnemyAttack();	// �G�l�~�[�U��
};
#endif // !_ENEMY_H_

