//*****************************************************************************
//
// �t�B�[���h����[FieldClass.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "FieldClass.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Field::Field()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �|�C���^
	m_VertexBuffField = NULL;

	// �N���X�|�C���^
	m_textureManager = new TextureManager();
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Field::~Field()
{
	// �|�C���^
	SAFE_RELEASE_POINT(m_VertexBuffField);

	// �N���X�|�C���^
	SAFE_RELEASE_CLASS_POINT(m_textureManager);
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
void Field::InitCoordinate(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//*****************************************************************************
//
// ���_�쐬
//
//*****************************************************************************
HRESULT Field::MakeVertex(int width, int height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffField, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�쐬
	VERTEX_3D* VetexBuffer;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
	m_VertexBuffField->Lock(0, 0, (void**)&VetexBuffer, 0);

	// ���_�o�b�t�@�̒��g�𖄂߂�
	// ���_���W(���[�J�����W = �`���`�����Ă�)
	// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
	// m_posFiled�͐��E�ł̈ʒu��
	
	// position
	VetexBuffer[0].Position = D3DXVECTOR3(-width, 0.0f, height);
	VetexBuffer[1].Position = D3DXVECTOR3(width, 0.0f, height);
	VetexBuffer[2].Position = D3DXVECTOR3(-width, 0.0f, -height);
	VetexBuffer[3].Position = D3DXVECTOR3(width, 0.0f, -height);

	// normal
	VetexBuffer[0].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	VetexBuffer[1].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	VetexBuffer[2].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	VetexBuffer[3].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// diffuse
	VetexBuffer[0].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	VetexBuffer[1].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	VetexBuffer[2].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	VetexBuffer[3].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

	// tex
	VetexBuffer[0].TexturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].TexturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].TexturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].TexturePosition = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_VertexBuffField->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// ���[���h�ϊ�
//
//*****************************************************************************
void Field::setWorldMatrix(D3DXMATRIX& mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X������������
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// ���s�ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���N�X�̏�����
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
}

//*****************************************************************************
//
// �e�N�X�`����`�悷��
//
//*****************************************************************************
void Field::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C�i��
	pDevice->SetStreamSource(0, m_VertexBuffField, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	Texture* p = m_textureManager->GetTexture(0);
	pDevice->SetTexture(0, p->TexturePoint);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}