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
	m_lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//m_directionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_waveAngle = 0.0f;
	m_isLife = true;

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
		RotationVecUp(D3DX_PI);
	}

	m_pos += m_lookVector * 0.15;	// �s�������ֈړ�
}

//*****************************************************************************
//
// �G�l�~�[�U��
//
//*****************************************************************************
void Enemy::EnemyAttack()
{

}