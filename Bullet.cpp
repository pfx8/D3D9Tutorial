//*****************************************************************************
//
// �e���� [Bullet.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Bullet.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Bullet::Bullet()
{
	m_upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_isUse = false;
	m_upSpeed = FIRST_UP_SPEED;

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
Bullet::~Bullet()
{
	// �N���X�|�C���^
	RELEASE_CLASS_POINT(m_model);
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);
}

//*****************************************************************************
//
// �v���[���[�ɂ���ăG�l�~�[�̍��W��ݒ�
//
//*****************************************************************************
void Bullet::InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip)
{
	m_isUse = true;	// �g����悤�ɂȂ�

	if(isShip == true)
		m_isEnemyBullet = false;
	else
		m_isEnemyBullet = true;

	// �ʒu��ݒ�
	m_pos = pos;
	m_pos.y = 1.5f + rand()%3;
	m_lookVector = moveVector * ((rand()%60 + 40) / 100.0f * 2.2f);	// �s��������ݒ�

	m_boundingBox->InitBox(2, 3, 2, 0.1f);	// �o�E���f�B���O�{�b�N�X��������
}

//*****************************************************************************
//
// �G�l�~�[�ړ�
//
//*****************************************************************************
void Bullet::BulletMove(D3DXVECTOR2 planeSize)
{
	m_pos -= m_lookVector * MOVE_SPEED;	// �s�������ֈړ�
	
	// �����ʒu�̌v�Z 
	m_upSpeed += ACCELERARION;
	m_pos.y += 0.5f * (m_upSpeed)* ONE_FRAME_TIME;

	// �n�}�͈̔͂𒴂�����A�e������
	if (/*m_pos.x >= planeSize.x || m_pos.x <= -planeSize.x || m_pos.z >= planeSize.y || m_pos.z <= -planeSize.y ||*/ m_pos.y <= 0.0f)
	{
		// �������琔�l��S��������
		m_isUse = false;
		m_upSpeed = FIRST_UP_SPEED;
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}
}

//*****************************************************************************
//
// �G�l�~�[�U��
//
//*****************************************************************************
void Bullet::CheckBulletAndShip()
{

}