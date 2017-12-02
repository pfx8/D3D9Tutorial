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
	
	m_name = " ";

	m_Speed = D3DXVECTOR3(1.5f, 0.0f, 0.0f);

	// �N���X�|�C���^
	m_mesh = new Mesh();
	m_message = new DebugMessage();
	m_boundingBox = new BoundingBox();

	InitMemberList();	// �����o�[���X�g�����

	m_BoundingBoxON = true;	// �o�E���f�B���O�{�b�N�X��`�悷��
}

//*****************************************************************************
//
// �v���C�x�[�g�����o�[���X�g������
//
//*****************************************************************************
void Character::InitMemberList()
{
	m_MemberList["pos"] = &m_pos;
	m_MemberList["rot"] = &m_rot;
	m_MemberList["scl"] = &m_scl;
	m_MemberList["speed"] = &m_Speed;
	m_MemberList["mesh"] = &m_mesh;
	m_MemberList["message"] = &m_message;
	m_MemberList["boundingBox"] = &m_boundingBox;
	m_MemberList["name"] = &m_name;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Character::~Character()
{
	// �N���X�|�C���^
	SAFE_RELEASE_CLASS_POINT(m_mesh);
	SAFE_RELEASE_CLASS_POINT(m_message);
	SAFE_RELEASE_CLASS_POINT(m_boundingBox);
}

//*****************************************************************************
//
// ���[���h�ϊ�
//
//*****************************************************************************
void Character::SetWorldMatrix(D3DXMATRIX& mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); // �J�����̕��������Ǝg��
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���N�X�̏�����
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
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
void Character::InitCharacter(D3DXVECTOR3 pos)
{
	// �ʒu
	m_pos = pos;

	// �o�E���f�B���O�{�b�N�X������������
	m_boundingBox->InitBox(20, 30, 40, 0.4f);

	// DEBUG
}

//*****************************************************************************
//
// �L�����N�^�[�̕`��
//
//*****************************************************************************
void Character::Draw()
{
	// ���b�V����`�悷��
	m_mesh->DrawModel();

	// �o�E���f�B���O�{�b�N�X��`�悷��
	if (m_BoundingBoxON == true)
	{
		m_boundingBox->Draw();
	}
}

//*****************************************************************************
//
// �L�����N�^�[�ړ�
//
//*****************************************************************************
void Character::Move()
{
	m_pos.x -= m_Speed.x;
}

//*****************************************************************************
//
// �L�����N�^�[�X�V
//
//*****************************************************************************
void Character::Update()
{

}

//*****************************************************************************
//
// �L�����N�^�[�̃o�E���f�B���O�{�b�N�X���擾
//
//*****************************************************************************
BoundingBox* Character::GetBoundingBox()
{
	return m_boundingBox;
}

//*****************************************************************************
//
// �L�����N�^�[�ʒu���擾
//
//*****************************************************************************
D3DXVECTOR3* Character::GetPosition()
{
	return &m_pos;
}

//*****************************************************************************
//
// �����蔻��
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3* ObjectPos = Object->GetPosition();
	D3DXVECTOR3* ObjectSize = Object->GetBoundingBox()->GetSize();

	if (
		GetPosition()->x + GetBoundingBox()->GetSize()->x / 2 > ObjectPos->x - ObjectSize->x / 2 &&
		GetPosition()->x - GetBoundingBox()->GetSize()->x / 2 < ObjectPos->x + ObjectSize->x / 2 &&
		GetPosition()->y - GetBoundingBox()->GetSize()->y / 2 < ObjectPos->y + ObjectSize->y / 2 &&
		GetPosition()->y + GetBoundingBox()->GetSize()->y / 2 > ObjectPos->y - ObjectSize->y / 2 &&
		GetPosition()->z + GetBoundingBox()->GetSize()->z / 2 > ObjectPos->z - ObjectSize->z / 2 &&
		GetPosition()->z - GetBoundingBox()->GetSize()->z / 2 < ObjectPos->z + ObjectSize->z / 2
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
// ���b�V�����擾
//
//*****************************************************************************
Mesh* Character::GetMesh()
{
	return m_mesh;
}