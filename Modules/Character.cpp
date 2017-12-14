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
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_directionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �N���X�|�C���^
	m_model = new Model();
	m_message = new DebugMessage();
	m_boundingBox = new BoundingBox();
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
// ���[���h�ϊ�
//
//*****************************************************************************
void Character::SetWorldMatrix(D3DXMATRIX* mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); // �J�����̕��������Ǝg��
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRot);

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTranslate);

	// ���[���h�}�g���N�X�̏�����
	pDevice->SetTransform(D3DTS_WORLD, mtxWorld);
}

//*****************************************************************************
//
// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	m_message->DrawPosMessage("Car1", m_pos, D3DXVECTOR2(0, float(row * 18 * 2)));
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
void Character::InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction)
{
	m_pos = pos;	// �ʒu
	m_directionVector = direction; // �v���[���[�̌���
	m_boundingBox->InitBox(20, 30, 40, 0.4f);	// �o�E���f�B���O�{�b�N�X��������
}

//*****************************************************************************
//
// �L�����N�^�[�̕`��
//
//*****************************************************************************
void Character::Draw(Shader* shader)
{
	m_model->DrawModel(shader);			// ���b�V����`�悷��
	if (m_boundingBox->m_isBoundingBoxDraw == true)
	{
		m_boundingBox->Draw(shader);	// �o�E���f�B���O�{�b�N�X��`�悷��
	}
}

//*****************************************************************************
//
// �L�����N�^�[�ړ�
//
//*****************************************************************************
void Character::Move()
{
	m_pos.x -= m_directionVector.x;
}

//*****************************************************************************
//
// �L�����N�^�[�X�V
//
//*****************************************************************************
void Character::Update(D3DXMATRIX* worldMatrix)
{
	
	SetWorldMatrix(worldMatrix);
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