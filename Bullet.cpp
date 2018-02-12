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
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->isUse = false;
	this->upSpeed = 0.0f;

	// �N���X�|�C���^
	this->model = new Model;
	this->message = new DebugMessage;
	this->boundingBox = new BoundingBox;

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Bullet::~Bullet()
{
	// �N���X�|�C���^
	RELEASE_CLASS_POINT(this->model);
	RELEASE_CLASS_POINT(this->message);
	RELEASE_CLASS_POINT(this->boundingBox);
}

//*****************************************************************************
//
// �v���[���[�ɂ���ăG�l�~�[�̍��W��ݒ�
//
//*****************************************************************************
void Bullet::InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip)
{
	this->isUse = true;	// �g����悤�ɂȂ�

	if(isShip == true)
		this->isEnemyBullet = false;
	else
		this->isEnemyBullet = true;

	// �ʒu��ݒ�
	this->pos = pos + moveVector * 6.0f;
	this->pos.y = 4.0f;
	this->lookVector = moveVector * ((rand()%60 + 40) / 100.0f * 2.2f);	// �s��������ݒ�
	this->upSpeed = FIRST_UP_SPEED + rand()%11;

	this->boundingBox->InitBox(2, 3, 2, 0.1f);	// �o�E���f�B���O�{�b�N�X��������
}

//*****************************************************************************
//
// �G�l�~�[�ړ�
//
//*****************************************************************************
void Bullet::BulletMove(D3DXVECTOR2 planeSize)
{
	this->pos += this->lookVector * MOVE_SPEED;	// �s�������ֈړ�
	
	// �����ʒu�̌v�Z 
	this->upSpeed += ACCELERARION;
	this->pos.y += 0.5f * (this->upSpeed)* ONE_FRAME_TIME;

	// �n�}�͈̔͂𒴂�����A�e������
	if ( this->pos.y <= 0.0f)
	{
		// �������琔�l��S��������
		this->isUse = false;
		this->upSpeed = FIRST_UP_SPEED;
		this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
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

//*****************************************************************************
//
// �L�����N�^�[�̕`��
//
//*****************************************************************************
void Bullet::Draw(CelShader* celShader, D3DXMATRIX* VPMatrix)
{
	// ���[���h�ϊ�
	SetWorldMatrix();

	// ���b�V����`�悷��
	this->model->DrawModel(celShader, &this->worldMatrix, VPMatrix, &lightMatrix, MT_bullet);
}