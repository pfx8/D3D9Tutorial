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

	m_Mesh	= new Mesh;

	m_Mesh->ReadXFile();
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Character::~Character()
{
	SAFE_RELEASE_CLASS_POINT(m_Mesh);
}

//*****************************************************************************
//
// ���[���h�ϊ�
//
//*****************************************************************************
void Character::setWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// ���[���h�}�g���b�N�X�̏�����
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