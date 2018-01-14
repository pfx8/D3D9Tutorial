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
	m_upSpeed = FIRST_SPEED;

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
void Bullet::InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector)
{
	m_isUse = true;	// �g����悤�ɂȂ�
	
	// �ʒu��ݒ�
	m_pos = pos;
	m_pos.y = 3.5f;
	m_lookVector = moveVector;	// �s��������ݒ�

	m_boundingBox->InitBox(3, 13, 3, 0.1f);	// �o�E���f�B���O�{�b�N�X��������
}

//*****************************************************************************
//
// �G�l�~�[�ړ�
//
//*****************************************************************************
void Bullet::BulletMove()
{
	m_pos -= m_lookVector * 0.1f;	// �s�������ֈړ�
	
	// �����ʒu�̌v�Z 
	m_upSpeed += ACCELERARION;
	m_pos.y += 0.5f * (m_upSpeed)* ONE_FRAME_TIME;

	// �n�}�͈̔͂𒴂�����A�e������
	if (m_pos.x >= 90.0f || m_pos.x <= -90.0f || m_pos.z >= 90.0f || m_pos.z <= -90.0f || m_pos.y <= 0.0f)
	{
		// �������琔�l��S��������
		m_isUse = false;
		m_upSpeed = FIRST_SPEED;
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