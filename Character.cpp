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

	m_Speed = 1.5f;

	// �N���X�|�C���^
	m_Mesh = new Mesh();
	m_Message = new DebugMessage();
	m_BoundingBox = new BoundingBox();
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Character::~Character()
{
	// �N���X�|�C���^
	SAFE_RELEASE_CLASS_POINT(m_Mesh);
	SAFE_RELEASE_CLASS_POINT(m_Message);
	SAFE_RELEASE_CLASS_POINT(m_BoundingBox);
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
	m_Message->DrawPosMessage("Car1", m_pos, D3DXVECTOR2(0, float(row * 18 * 2)));
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
void Character::SetCoordinate(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// �o�E���f�B���O�{�b�N�X������������
	m_BoundingBox->InitBox(20, 30, 40, 0.4f);
	
	// DEBUG
}

//*****************************************************************************
//
// �L�����N�^�[�̖��O�����߂�
//
//*****************************************************************************
void Character::SetName(std::string name)
{
	m_name = name;

	// ���O�Ń��b�V���ƃe�N�X�`����ǂݍ���
	ChooseMesh(m_name);
}

//*****************************************************************************
//
// ���O�Ń��b�V�����쐬
//
//*****************************************************************************
void Character::ChooseMesh(std::string name)
{
	m_Mesh->SetMesh(name);
}

//*****************************************************************************
//
// �L�����N�^�[�̕`��
//
//*****************************************************************************
void Character::Draw()
{
	// ���b�V����`�悷��
	m_Mesh->DrawModel();

	// �o�E���f�B���O�{�b�N�X��`�悷��
	m_BoundingBox->Draw();
}

//*****************************************************************************
//
// �L�����N�^�[�ړ�
//
//*****************************************************************************
void Character::Move()
{
	m_pos.x -= m_Speed;
}

//*****************************************************************************
//
// �L�����N�^�[�X�V
//
//*****************************************************************************
void Character::Update()
{
	if (GetKeyboardPress(DIK_A))			// key A
	{
		m_pos.x -= m_Speed;
	}
	if (GetKeyboardPress(DIK_D))			// key D
	{
		m_pos.x += m_Speed;
	}
	if (GetKeyboardPress(DIK_W))			// key W
	{
		m_pos.z += m_Speed;
	}
	if (GetKeyboardPress(DIK_S))			// key S
	{
		m_pos.z -= m_Speed;
	}
}

//*****************************************************************************
//
// �L�����N�^�[�̃o�E���f�B���O�{�b�N�X���擾
//
//*****************************************************************************
BoundingBox* Character::GetBoundingBox()
{
	return m_BoundingBox;
}

//*****************************************************************************
//
// �o�E���f�B���O�{�b�N�X�ʒu���擾
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
	return m_Mesh;
}