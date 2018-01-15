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
	m_upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookVector = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_directionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_waveAngle = 0.0f;
	m_isLife = true;
	m_time = 0.016 * 120;
	m_isAttack = false;
	m_attackTime = 0.016 * 180;

	// �N���X�|�C���^
	m_model = new Model;
	m_message = new DebugMessage;
	m_boundingBox = new BoundingBox;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Enemy::~Enemy()
{
	// �N���X�|�C���^
	RELEASE_CLASS_POINT(m_model);
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);
}

//*****************************************************************************
//
// �G�l�~�[���W��ݒ�
//
//*****************************************************************************
void Enemy::InitEnemy(D3DXVECTOR3 pos)
{
	m_pos = pos;	// �ʒu
	m_boundingBox->InitBox(5, 11, 10, 0.1f);	// �o�E���f�B���O�{�b�N�X��������
}

//*****************************************************************************
//
// �G�l�~�[�ړ�
//
//*****************************************************************************
void Enemy::EnemyMove(D3DXVECTOR2 planeSize)
{
	// �n�}�͈̔͂𒴂�����A�t�����ɍs��
	if (m_pos.x >= planeSize.x * 0.8f || m_pos.x <= -planeSize.x * 0.8f || m_pos.z >= planeSize.y * 0.8f || m_pos.z <= -planeSize.y * 0.8f)
	{
		if (m_time == 0.016f * 120)
		{
			//RotationVecUp(D3DX_PI);
			Trans(D3DX_PI);
		}
	}

	m_time -= 0.016f;
	if (m_time <= 0.0f)
	{
		m_time = 0.016f * 120;
	}

	if (m_isAttack == true)
	{
		m_attackTime -= 0.016f;
		if (m_attackTime <= 0.0f)
		{
			m_isAttack = false;
			m_attackTime = 0.016f * 120;
		}
	}

	m_pos -= m_lookVector * 0.1f;	// �s�������ֈړ�
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
	D3DXVECTOR3 playerPos = player->m_pos;
	D3DXVECTOR3 playerBoxSize = player->m_boundingBox->m_size;
	// �G�l�~�[
	D3DXVECTOR3 enemyPos = m_pos;
	D3DXVECTOR3 enemyBoxSize;
	enemyBoxSize.x = m_lookVector.x * 100;
	enemyBoxSize.y = 10;
	enemyBoxSize.z = m_lookVector.z * 100;

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
	if (m_rot.y > D3DX_PI * 2.0f || m_rot.y < -D3DX_PI * 2.0f)
	{
		m_rot.y = 0;
	}

	// �p�x���L�^����
	m_rot.y -= angle;

	// �V�����E�����x�N�g�����v�Z����
	//m_rightVector.x = cosf(m_rot.y);
	//m_rightVector.z = sinf(m_rot.y);

	// �V�������������x�N�g�����v�Z����
	//m_lookVector.x = cosf(m_rot.y + D3DX_PI / 2);
	//m_lookVector.z = sinf(m_rot.y + D3DX_PI / 2);
	
	m_lookVector.x = cosf(-m_rot.y + D3DX_PI / 2);
	m_lookVector.z = sinf(-m_rot.y + D3DX_PI / 2);
}