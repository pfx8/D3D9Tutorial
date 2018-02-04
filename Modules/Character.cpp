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
	m_upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_waveAngle = 0.0f;
	m_speedCoefficient = 0.0f;
	m_leverLevel = 0;

	// �N���X�|�C���^
	m_message = new DebugMessage;
	m_boundingBox = new BoundingBox;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Character::~Character()
{
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);

	RELEASE_CLASS_ARRY_POINT(m_model);
}

//*****************************************************************************
//
// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	m_message->DrawPosMessage("Pos", m_pos, D3DXVECTOR2(0, float((row) * 18)));
	m_message->DrawPosMessage("Look", m_lookVector, D3DXVECTOR2(0, float((row + 1) * 18)));
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
void Character::InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction, int modelNum)
{
	m_pos = pos;	// �ʒu
	
	m_modelNum = modelNum;
	m_model = new Model[m_modelNum]; // ���f���𐔂ɂ���ď�����
}

//*****************************************************************************
//
// �L�����N�^�[�̕`��
//
//*****************************************************************************
void Character::Draw(CelShader* celShader)
{
	m_model->DrawModel(celShader);	// ���b�V����`�悷��
}

//*****************************************************************************
//
// �L�����N�^�[�X�V
//
//*****************************************************************************
void Character::Update(float rot)
{
	// �g
	m_waveAngle = rot;
	if (m_waveAngle > D3DX_PI * 2.0f)
		m_waveAngle = 0.0f;
	m_pos.y = 0.8 * sinf(m_waveAngle);

	// �ړ�
	switch (m_leverLevel)
	{
	case LL_BACK:
		m_speedCoefficient -= 0.0001f;
		if (m_speedCoefficient <= MAX_BACK_COEFFICIENT)
			m_speedCoefficient = MAX_BACK_COEFFICIENT;
		break;
	case LL_STOP:
		m_speedCoefficient = 0.0f;
		break;
	case LL_FRONT:
		m_speedCoefficient += 0.0001f;
		if (m_speedCoefficient >= MAX_FRONT_COEFFICIENT)
			m_speedCoefficient = MAX_FRONT_COEFFICIENT;
		break;
	default:
		break;
	}
	MoveAlongVecLook(m_speedCoefficient);
}

//*****************************************************************************
//
// �����蔻��
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3 ObjectPos = Object->m_pos;
	D3DXVECTOR3 ObjectSize = Object->m_boundingBox->m_size;

	if (
		m_pos.x + m_boundingBox->m_size.x / 2 > ObjectPos.x - ObjectSize.x / 2 &&
		m_pos.x - m_boundingBox->m_size.x / 2 < ObjectPos.x + ObjectSize.x / 2 &&
		m_pos.y - m_boundingBox->m_size.y / 2 < ObjectPos.y + ObjectSize.y / 2 &&
		m_pos.y + m_boundingBox->m_size.y / 2 > ObjectPos.y - ObjectSize.y / 2 &&
		m_pos.z + m_boundingBox->m_size.z / 2 > ObjectPos.z - ObjectSize.z / 2 &&
		m_pos.z - m_boundingBox->m_size.z / 2 < ObjectPos.z + ObjectSize.z / 2
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
	m_rot.y += angle;

	if (m_rot.y > D3DX_PI / 6.0f)
	{
		m_rot.y = D3DX_PI / 6.0f;
	}
	if (m_rot.y < -D3DX_PI / 6.0f)
	{
		m_rot.y = -D3DX_PI / 6.0f;
	}

	// �V�����E�����x�N�g�����v�Z����
	m_rightVector.x = cosf(m_rot.y + D3DX_PI / 2);
	m_rightVector.z = sinf(m_rot.y + D3DX_PI / 2);

	// �V�������������x�N�g�����v�Z����
	m_lookVector.x = cosf(m_rot.y);
	m_lookVector.z = sinf(m_rot.y);
}

//*****************************************************************************
//
// ���o�[�̑���ɂ���ăX�s�[�h��ς��
//
//*****************************************************************************
void Character::ChangeLever(LEVER_LEVEL scalars)
{
	switch (m_leverLevel)
	{
	case LL_BACK:
		if (scalars == LL_STOP)
		{
			m_leverLevel = LL_STOP;
			m_speedCoefficient += 0.0001f;
			if (m_speedCoefficient >= 0.0f)
				m_speedCoefficient = 0.0f;
		}
		if (scalars == LL_FRONT)
		{
			m_leverLevel = LL_FRONT;
			m_speedCoefficient += 0.0001f;
			if (m_speedCoefficient >= MAX_FRONT_COEFFICIENT)
				m_speedCoefficient = MAX_FRONT_COEFFICIENT;
		}
		break;
	case LL_STOP:
		if (scalars == LL_BACK)
		{
			m_leverLevel = LL_BACK;
			m_speedCoefficient -= 0.0001f;
			if (m_speedCoefficient <= MAX_BACK_COEFFICIENT)
				m_speedCoefficient = MAX_BACK_COEFFICIENT;
		}
		if (scalars == LL_FRONT)
		{
			m_leverLevel = LL_FRONT;
			m_speedCoefficient += 0.0001f;
			if (m_speedCoefficient >= MAX_FRONT_COEFFICIENT)
				m_speedCoefficient = MAX_FRONT_COEFFICIENT;
		}
		break;
	case LL_FRONT:
		if (scalars == LL_BACK)
		{
			m_leverLevel = LL_BACK;
			m_speedCoefficient -= 0.0001f;
			if (m_speedCoefficient <= MAX_BACK_COEFFICIENT)
				m_speedCoefficient = MAX_BACK_COEFFICIENT;
		}
		if (scalars == LL_STOP)
		{
			m_leverLevel = LL_STOP;
			m_speedCoefficient -= 0.0001f;
			if (m_speedCoefficient <= 0.0f)
				m_speedCoefficient = 0.0f;
		}
		break;
	default:
		break;
	}

	// test
	switch (m_leverLevel)
	{
	case LL_BACK:
		std::cout << "��" << std::endl; break;
	case LL_STOP:
		std::cout << "��" << std::endl; break;
	case LL_FRONT:
		std::cout << "�O" << std::endl; break;
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
	m_pos += m_lookVector * unit;

	return m_lookVector * unit;
}

//*****************************************************************************
//
// ���[���h�ϊ���ݒ�
//
//*****************************************************************************
void Character::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_worldMatrix);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);
}