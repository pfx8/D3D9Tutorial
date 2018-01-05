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
	//m_directionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	r = 0.0f;

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
Character::~Character()
{
	// �N���X�|�C���^
	RELEASE_CLASS_POINT(m_model);
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);
}

//*****************************************************************************
//
// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	m_message->DrawPosMessage("Hero Pos", m_pos, D3DXVECTOR2(0, float(row * 18)));
	m_message->DrawPosMessage("H-look", m_lookVector, D3DXVECTOR2(0, float((row + 1) * 18)));
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
void Character::InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction)
{
	m_pos = pos;	// �ʒu
	//m_directionVector = direction; // �v���[���[�̌���
	m_boundingBox->InitBox(3, 13, 3, 0.1f);	// �o�E���f�B���O�{�b�N�X��������
}

//*****************************************************************************
//
// �L�����N�^�[�̕`��
//
//*****************************************************************************
void Character::Draw(CelShader* celShader)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxOrgin, mtxRot, mtxTranslate;

	D3DXMatrixIdentity(&mtxOrgin);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxOrgin, &mtxOrgin, &mtxRot);

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxOrgin, &mtxOrgin, &mtxTranslate);

	celShader->m_effectPoint->SetMatrix(celShader->m_changeMatrixHandle, &mtxOrgin);

	m_model->DrawModel(celShader);	// ���b�V����`�悷��

	if (m_boundingBox->m_isBoundingBoxDraw == true)
	{
		m_boundingBox->Draw(celShader);	// �o�E���f�B���O�{�b�N�X��`�悷��
	}
}

//*****************************************************************************
//
// �L�����N�^�[�ړ�
//
//*****************************************************************************
void Character::Move()
{
	//m_pos.x -= m_directionVector.x;
	//m_pos.z -= m_directionVector.z;
}

//*****************************************************************************
//
// �L�����N�^�[�X�V
//
//*****************************************************************************
void Character::Update(float rot)
{
	r = rot;

	if (r > D3DX_PI * 2.0f)
		r = 0.0f;

	m_pos.y = 0.7 * sinf(r);
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
	if (m_rot.y > D3DX_PI * 2.0f || m_rot.y < -D3DX_PI * 2.0f)
	{
		m_rot.y = 0;
	}

	// �p�x���L�^����
	m_rot.y -= angle;

	// �V�����E�����x�N�g�����v�Z����
	m_rightVector.x = cosf(m_rot.y);
	m_rightVector.z = sinf(m_rot.y);

	// �V�������������x�N�g�����v�Z����
	m_lookVector.x = cosf(m_rot.y + D3DX_PI / 2);
	m_lookVector.z = sinf(m_rot.y + D3DX_PI / 2);

	//m_directionVector.x = cosf(m_rot.y + D3DX_PI / 2);
	//m_directionVector.z = sinf(m_rot.y + D3DX_PI / 2);
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