//*****************************************************************************
//
// �L�����N�^�[�x�[�X���� [Character.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Character.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Character::Character()
{
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	this->waveAngle = 0.0f;
	this->speed = 0.0f;

	leverLevel = LL_STOP;

	// �N���X�|�C���^
	this->message = new DebugMessage;
	this->boundingBox = new BoundingBox;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Character::~Character()
{
	RELEASE_CLASS_POINT(this->message);
	RELEASE_CLASS_POINT(this->boundingBox);

	RELEASE_CLASS_ARRY_POINT(this->model);
}

//*****************************************************************************
//
// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	this->message->DrawPosMessage("Pos", this->pos, D3DXVECTOR2(0, float((row + 0) * 18)));
}

//*****************************************************************************
//
// �L�����N�^�[�̕`��
//
//*****************************************************************************
void Character::Draw(CelShader* celShader)
{
	this->model->DrawModel(celShader);	// ���b�V����`�悷��
}

//*****************************************************************************
//
// �L�����N�^�[�X�V
//
//*****************************************************************************
void Character::Update(float rot)
{
	// �g�ɍ��킹�ėh���
	this->waveAngle = rot;
	if (this->waveAngle > D3DX_PI * 2.0f)
		this->waveAngle = 0.0f;
	this->pos.y = 0.8 * sinf(this->waveAngle);

	// �ړ�
	switch (leverLevel)
	{
	case LL_FRONT:
		this->speed += 0.0001f;
		if (this->speed >= MAX_FRONT_SPEED_COEFFICIENT)
			this->speed = MAX_FRONT_SPEED_COEFFICIENT;
		break;
	case LL_STOP:
		this->speed = 0.0f;
		break;
	case LL_BACK:
		this->speed -= 0.0001f;
		if (this->speed <= MAX_BACK_SPEED_COEFFICIENT)
			this->speed = MAX_BACK_SPEED_COEFFICIENT;
		break;
	default:
		break;
	}
	MoveAlongVecLook(this->speed);
}

//*****************************************************************************
//
// ������̃x�N�g���ɂ��ĉ�]
//
//*****************************************************************************
void Character::RotationVecUp(float angle)
{
	// �p�x���L�^����
	this->rot.y += angle;

	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationAxis(&rotMatrix, &this->upVector, angle);					// ��]�s������
	D3DXVec3TransformCoord(&this->lookVector, &this->lookVector, &rotMatrix);	// �J�����̐V�������W���v�Z����

	D3DXVec3Normalize(&this->lookVector, &this->lookVector);
	D3DXVec3Cross(&this->rightVector, &this->lookVector, &this->upVector);
	D3DXVec3Normalize(&this->rightVector, &this->rightVector);
	D3DXVec3Cross(&this->upVector, &this->rightVector, &this->lookVector);
	D3DXVec3Normalize(&this->upVector, &this->upVector);

}

//*****************************************************************************
//
// ���o�[�̑���ɂ���ăX�s�[�h��ς��
//
//*****************************************************************************
void Character::ChangeLever(LEVER_LEVEL level)
{
	switch (leverLevel)
	{
	case LL_FRONT:
		if (level == LL_STOP)
		{
			leverLevel = LL_STOP;
		}
		if (level == LL_BACK)
		{
			leverLevel = LL_BACK;
		}
		break;
	case LL_STOP:
		if (level == LL_FRONT)
		{
			leverLevel = LL_FRONT;
		}
		if (level == LL_BACK)
		{
			leverLevel = LL_BACK;
		}
		break;
	case LL_BACK:
		if (level == LL_FRONT)
		{
			leverLevel = LL_FRONT;
		}
		if (level == LL_STOP)
		{
			leverLevel = LL_STOP;
		}
		break;
	default:
		break;
	}

	//�R���\�[���ɏo�����b�Z�[�W
	switch (leverLevel)
	{
	case LL_FRONT:
		std::cout << "�O" << std::endl; break;
	case LL_STOP:
		std::cout << "��" << std::endl; break;
	case LL_BACK:
		std::cout << "��" << std::endl; break;
	default:
		break;
	}

}

//*****************************************************************************
//
// ���������ɉ����Ĉړ�
//
//*****************************************************************************
D3DXVECTOR3 Character::MoveAlongVecLook(float speedCoefficient)
{
	this->pos += this->lookVector * speedCoefficient;

	return this->lookVector * speedCoefficient;
}

//*****************************************************************************
//
// ���[���h�ϊ���ݒ�
//
//*****************************************************************************
void Character::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&this->worldMatrix);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, this->scl.x, this->scl.y, this->scl.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&this->lightMatrix, this->rot.y, this->rot.x, this->rot.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &this->lightMatrix);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);

	// ���C�g�}�g���b�N�X
	D3DXMatrixTranslation(&mtxTranslate, 0, this->pos.y, 0);
	D3DXMatrixMultiply(&this->lightMatrix, &this->lightMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// �����蔻��
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3 ObjectPos = Object->pos;
	D3DXVECTOR3 ObjectSize = Object->boundingBox->size;

	if (
		this->pos.x + this->boundingBox->size.x / 2 > ObjectPos.x - ObjectSize.x / 2 &&
		this->pos.x - this->boundingBox->size.x / 2 < ObjectPos.x + ObjectSize.x / 2 &&
		this->pos.y - this->boundingBox->size.y / 2 < ObjectPos.y + ObjectSize.y / 2 &&
		this->pos.y + this->boundingBox->size.y / 2 > ObjectPos.y - ObjectSize.y / 2 &&
		this->pos.z + this->boundingBox->size.z / 2 > ObjectPos.z - ObjectSize.z / 2 &&
		this->pos.z - this->boundingBox->size.z / 2 < ObjectPos.z + ObjectSize.z / 2
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}