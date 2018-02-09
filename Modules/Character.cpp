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
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	this->rightVector = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	this->waveAngle = 0.0f;
	this->speedCoefficient = 0.0f;
	leverLevel = 0;

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
// ���W��ݒ�
//
//*****************************************************************************
void Character::InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction, int modelNum)
{
	this->pos = pos;	// �ʒu
	
	modelNum = modelNum;
	this->model = new Model[modelNum]; // ���f���𐔂ɂ���ď�����
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
	// �g
	this->waveAngle = rot;
	if (this->waveAngle > D3DX_PI * 2.0f)
		this->waveAngle = 0.0f;
	this->pos.y = 0.8 * sinf(this->waveAngle);

	// �ړ�
	switch (leverLevel)
	{
	case LL_BACK:
		this->speedCoefficient -= 0.0001f;
		if (this->speedCoefficient <= MAX_BACK_COEFFICIENT)
			this->speedCoefficient = MAX_BACK_COEFFICIENT;
		break;
	case LL_STOP:
		this->speedCoefficient = 0.0f;
		break;
	case LL_FRONT:
		this->speedCoefficient += 0.0001f;
		if (this->speedCoefficient >= MAX_FRONT_COEFFICIENT)
			this->speedCoefficient = MAX_FRONT_COEFFICIENT;
		break;
	default:
		break;
	}
	MoveAlongVecLook(this->speedCoefficient);
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

//*****************************************************************************
//
// ������̃x�N�g���ɂ��ĉ�]
//
//*****************************************************************************
void Character::RotationVecUp(float angle)
{
	// �p�x���L�^����
	this->rot.y += angle;

	if (this->rot.y > D3DX_PI / 6.0f)
	{
		this->rot.y = D3DX_PI / 6.0f;
	}
	if (this->rot.y < -D3DX_PI / 6.0f)
	{
		this->rot.y = -D3DX_PI / 6.0f;
	}

	// �V�����E�����x�N�g�����v�Z����
	this->rightVector.x = cosf(this->rot.y + D3DX_PI / 2);
	this->rightVector.z = sinf(this->rot.y + D3DX_PI / 2);

	// �V�������������x�N�g�����v�Z����
	this->lookVector.x = cosf(this->rot.y);
	this->lookVector.z = sinf(this->rot.y);
}

//*****************************************************************************
//
// ���o�[�̑���ɂ���ăX�s�[�h��ς��
//
//*****************************************************************************
void Character::ChangeLever(LEVER_LEVEL scalars)
{
	switch (leverLevel)
	{
	case LL_BACK:
		if (scalars == LL_STOP)
		{
			leverLevel = LL_STOP;
			this->speedCoefficient += 0.0001f;
			if (this->speedCoefficient >= 0.0f)
				this->speedCoefficient = 0.0f;
		}
		if (scalars == LL_FRONT)
		{
			leverLevel = LL_FRONT;
			this->speedCoefficient += 0.0001f;
			if (this->speedCoefficient >= MAX_FRONT_COEFFICIENT)
				this->speedCoefficient = MAX_FRONT_COEFFICIENT;
		}
		break;
	case LL_STOP:
		if (scalars == LL_BACK)
		{
			leverLevel = LL_BACK;
			this->speedCoefficient -= 0.0001f;
			if (this->speedCoefficient <= MAX_BACK_COEFFICIENT)
				this->speedCoefficient = MAX_BACK_COEFFICIENT;
		}
		if (scalars == LL_FRONT)
		{
			leverLevel = LL_FRONT;
			this->speedCoefficient += 0.0001f;
			if (this->speedCoefficient >= MAX_FRONT_COEFFICIENT)
				this->speedCoefficient = MAX_FRONT_COEFFICIENT;
		}
		break;
	case LL_FRONT:
		if (scalars == LL_BACK)
		{
			leverLevel = LL_BACK;
			this->speedCoefficient -= 0.0001f;
			if (this->speedCoefficient <= MAX_BACK_COEFFICIENT)
				this->speedCoefficient = MAX_BACK_COEFFICIENT;
		}
		if (scalars == LL_STOP)
		{
			leverLevel = LL_STOP;
			this->speedCoefficient -= 0.0001f;
			if (this->speedCoefficient <= 0.0f)
				this->speedCoefficient = 0.0f;
		}
		break;
	default:
		break;
	}

	// test
	switch (leverLevel)
	{
	case LL_BACK:
		std::cout << "�O" << std::endl; break;
	case LL_STOP:
		std::cout << "��" << std::endl; break;
	case LL_FRONT:
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
D3DXVECTOR3 Character::MoveAlongVecLook(float unit)
{
	this->pos += this->lookVector * unit;

	return this->lookVector * unit;
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