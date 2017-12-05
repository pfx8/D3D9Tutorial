//*****************************************************************************
//
// ���ʏ���[Plane.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Plane.h"

#include "ResourcesManager.h"
//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Plane::Plane()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �|�C���^
	m_planeVertexBuff = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Plane::~Plane()
{
	// �|�C���^
	RELEASE_POINT(m_planeVertexBuff);
	RELEASE_POINT(m_fieldTexture);
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
void Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;	// �ʒu
	MakeVertex(size.x, size.y);	// ���_�쐬
}

//*****************************************************************************
//
// ���W��ݒ�(���d�e�N�X�`��)
//
//*****************************************************************************
void Plane::InitPlaneDT(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;	// �ʒu
	MakeVertexDT(size.x, size.y);	// ���_�쐬
}

//*****************************************************************************
//
// ���_�쐬
//
//*****************************************************************************
HRESULT Plane::MakeVertex(int width, int height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_planeVertexBuff, NULL)))
	{
		std::cout << "[Error] ���_�o�b�t�@�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
		return E_FAIL;
	}

	// ���_�o�b�t�@�쐬
	VERTEX_3D* VetexBuffer;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
	m_planeVertexBuff->Lock(0, 0, (void**)&VetexBuffer, 0);

	// ���_�o�b�t�@�̒��g�𖄂߂�
	// ���_���W(���[�J�����W = �`���`�����Ă�)
	// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
	// m_posFiled�͐��E�ł̈ʒu��
	
	// position
	VetexBuffer[0].Position = D3DXVECTOR3(-width, 0.0f,  height);
	VetexBuffer[1].Position = D3DXVECTOR3( width, 0.0f,  height);
	VetexBuffer[2].Position = D3DXVECTOR3(-width, 0.0f, -height);
	VetexBuffer[3].Position = D3DXVECTOR3( width, 0.0f, -height);

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
	m_planeVertexBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// ���_�쐬(���d�e�N�X�`��)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDT(int width, int height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D_DT), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D_DT, D3DPOOL_MANAGED, &m_planeVertexBuff, NULL)))
	{
		std::cout << "[Error] ���_�o�b�t�@�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
		return E_FAIL;
	}

	// ���_�o�b�t�@�쐬
	VERTEX_3D_DT* VetexBuffer;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
	m_planeVertexBuff->Lock(0, 0, (void**)&VetexBuffer, 0);

	// ���_�o�b�t�@�̒��g�𖄂߂�
	// ���_���W(���[�J�����W = �`���`�����Ă�)
	// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
	// m_posFiled�͐��E�ł̈ʒu��

	// position
	VetexBuffer[0].Position = D3DXVECTOR3(-width, 0.0f, height);
	VetexBuffer[1].Position = D3DXVECTOR3(width, 0.0f, height);
	VetexBuffer[2].Position = D3DXVECTOR3(-width, 0.0f, -height);
	VetexBuffer[3].Position = D3DXVECTOR3(width, 0.0f, -height);

	// tex1
	VetexBuffer[0].TexturePosition0 = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].TexturePosition0 = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].TexturePosition0 = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].TexturePosition0 = D3DXVECTOR2(1.0f, 1.0f);

	// tex2
	VetexBuffer[0].TexturePosition1 = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].TexturePosition1 = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].TexturePosition1 = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].TexturePosition1 = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_planeVertexBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// ���[���h�ϊ�
//
//*****************************************************************************
void Plane::SetWorldMatrix(D3DXMATRIX& mtxWorld)
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
void Plane::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C�i��
	pDevice->SetStreamSource(0, m_planeVertexBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_fieldTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//*****************************************************************************
//
// �e�N�X�`����`�悷��(PixelShader)
//
//*****************************************************************************
void Plane::Draw(LPDIRECT3DTEXTURE9 texture, D3DXCONSTANT_DESC desc1, D3DXCONSTANT_DESC desc2)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, m_planeVertexBuff, 0, sizeof(VERTEX_3D_DT));	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C�i��
	pDevice->SetFVF(FVF_VERTEX_3D_DT);	// ���_�t�H�[�}�b�g�̐ݒ�

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(desc1.RegisterIndex, m_fieldTexture);
	pDevice->SetTexture(desc2.RegisterIndex, texture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//*****************************************************************************
//
// �e�N�X�`����ݒ�
//
//*****************************************************************************
//void Plane::SetTexture(LPDIRECT3DTEXTURE9* point)
//{
//	m_fieldTexture = *point;
//}