//*****************************************************************************
//
// �L�����N�^�[�x�[�X�N���X [CharacterClass.cpp]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#include "CharacterClass.h"

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

	// �N���X�|�C���^
	m_Mesh = new Mesh();
	m_Message = new OutputMessage();
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
}

//*****************************************************************************
//
// ���[���h�ϊ�
//
//*****************************************************************************
void Character::setWorldMatrix(D3DXMATRIX& mtxWorld)
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
// �L�����N�^�[�̃��b�V���̎擾
//
//*****************************************************************************
Mesh* Character::GetMesh()
{
	return m_Mesh;
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
void Character::InitCoordinate(D3DXVECTOR3 pos)
{
	m_pos = pos;
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