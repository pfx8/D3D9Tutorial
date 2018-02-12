//*****************************************************************************
//
// �G�l�~�[���� [Enemy.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Enemy.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Enemy::Enemy()
{
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//this->directionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->waveAngle = 0.0f;
	this->isLife = true;
	this->time = 0.016 * 120;
	this->isAttack = false;
	this->attackTime = 0.016 * 180;

	// �N���X�|�C���^
	this->message = new DebugMessage;
	this->boundingBox = new BoundingBox;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Enemy::~Enemy()
{
	// �N���X�|�C���^
	RELEASE_CLASS_POINT(this->message);
	RELEASE_CLASS_POINT(this->boundingBox);
}

//*****************************************************************************
//
// �G�l�~�[���W��ݒ�
//
//*****************************************************************************
void Enemy::InitEnemy(D3DXVECTOR3 pos)
{
	this->pos = pos;	// �ʒu
	this->boundingBox->InitBox(5, 11, 10, 0.1f);	// �o�E���f�B���O�{�b�N�X��������
}

//*****************************************************************************
//
// �G�l�~�[�ړ�
//
//*****************************************************************************
void Enemy::EnemyMove(D3DXVECTOR2 planeSize)
{
	// �n�}�͈̔͂𒴂�����A�t�����ɍs��
	if (this->pos.x >= planeSize.x * 0.8f || this->pos.x <= -planeSize.x * 0.8f || this->pos.z >= planeSize.y * 0.8f || this->pos.z <= -planeSize.y * 0.8f)
	{
		if (this->time == 0.016f * 120)
		{
			//RotationVecUp(D3DX_PI);
			Trans(D3DX_PI);
		}
	}

	this->time -= 0.016f;
	if (this->time <= 0.0f)
	{
		this->time = 0.016f * 120;
	}

	if (this->isAttack == true)
	{
		this->attackTime -= 0.016f;
		if (this->attackTime <= 0.0f)
		{
			this->isAttack = false;
			this->attackTime = 0.016f * 120;
		}
	}

	this->pos -= this->lookVector * 0.1f;	// �s�������ֈړ�
}

//*****************************************************************************
//
// �G�l�~�[�U��
//
//*****************************************************************************
bool Enemy::EnemyAttack(Character* player)
{
	if (CheckBB(player) == true)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
//
// �v���[���[�𔭌����邩�ǂ����̔���
//
//*****************************************************************************
bool Enemy::CheckBB(Character* player)
{
	// �e
	D3DXVECTOR3 playerPos = player->pos;
	D3DXVECTOR3 playerBoxSize = player->boundingBox->size;
	// �G�l�~�[
	D3DXVECTOR3 enemyPos = this->pos;
	D3DXVECTOR3 enemyBoxSize;
	enemyBoxSize.x = this->lookVector.x * 100;
	enemyBoxSize.y = 10;
	enemyBoxSize.z = this->lookVector.z * 100;

	if (
		/*playerPos.x + playerBoxSize.x / 2 > enemyPos.x - enemyBoxSize.x / 2 &&
		playerPos.x - playerBoxSize.x / 2 < enemyPos.x + enemyBoxSize.x / 2 &&
		playerPos.y - playerBoxSize.y / 2 < enemyPos.y + enemyBoxSize.y / 2 &&
		playerPos.y + playerBoxSize.y / 2 > enemyPos.y - enemyBoxSize.y / 2 &&
		playerPos.z + playerBoxSize.z / 2 > enemyPos.z - enemyBoxSize.z / 2 &&
		playerPos.z - playerBoxSize.z / 2 < enemyPos.z + enemyBoxSize.z / 2*/
		playerPos.x + playerBoxSize.x / 2 > enemyPos.x - enemyBoxSize.x / 2 &&
		playerPos.x - playerBoxSize.x / 2 < enemyPos.x &&
		playerPos.y - playerBoxSize.y / 2 < enemyPos.y &&
		playerPos.y + playerBoxSize.y / 2 > enemyPos.y - enemyBoxSize.y / 2 &&
		playerPos.z + playerBoxSize.z / 2 > enemyPos.z - enemyBoxSize.z / 2 &&
		playerPos.z - playerBoxSize.z / 2 < enemyPos.z
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
void Enemy::Trans(float angle)
{
	if (this->rot.y > D3DX_PI * 2.0f || this->rot.y < -D3DX_PI * 2.0f)
	{
		this->rot.y = 0;
	}

	// �p�x���L�^����
	this->rot.y -= angle;

	// �V�����E�����x�N�g�����v�Z����
	//this->rightVector.x = cosf(this->rot.y);
	//this->rightVector.z = sinf(this->rot.y);

	// �V�������������x�N�g�����v�Z����
	//this->lookVector.x = cosf(this->rot.y + D3DX_PI / 2);
	//this->lookVector.z = sinf(this->rot.y + D3DX_PI / 2);
	
	this->lookVector.x = cosf(-this->rot.y + D3DX_PI / 2);
	this->lookVector.z = sinf(-this->rot.y + D3DX_PI / 2);
}