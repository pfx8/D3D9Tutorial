//*****************************************************************************
//
// ���ʏ���[Plane.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Plane.h"

#include "../ResourcesManager.h"
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
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Plane::~Plane()
{
	// �|�C���^
	RELEASE_POINT(m_vertexBuffer);
	RELEASE_POINT(m_fieldTexture);
	RELEASE_POINT(m_indexBuffer);
}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
void Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;	// �ʒu
	MakeVertexDecl(size.x, size.y);	// ���_�錾(shader)
}

//*****************************************************************************
//
// ���_�錾(Shader)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDecl(int width, int height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVERTEXELEMENT9 planeDecl[] =		// ���_�f�[�^�̃��C�A�E�g���`
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
		{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);	// ���_�f�[�^�����

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)))
	{
		std::cout << "[Error] ���_�o�b�t�@�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
		return E_FAIL;
	}

	// ���_�o�b�t�@�쐬
	VERTEX_3D* VetexBuffer;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
	m_vertexBuffer->Lock(0, 0, (void**)&VetexBuffer, 0);

	// ���_�o�b�t�@�̒��g�𖄂߂�
	// ���_���W(���[�J�����W = �`���`�����Ă�)
	// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
	// m_posFiled�͐��E�ł̈ʒu��

	// ���_���W�̐ݒ�
	VetexBuffer[0].position = D3DXVECTOR3(-width, 0.0f, height);
	VetexBuffer[1].position = D3DXVECTOR3(width, 0.0f, height);
	VetexBuffer[2].position = D3DXVECTOR3(-width, 0.0f, -height);
	VetexBuffer[3].position = D3DXVECTOR3(width, 0.0f, -height);

	// �@���x�N�g���̐ݒ�
	VetexBuffer[0].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VetexBuffer[1].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VetexBuffer[2].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VetexBuffer[3].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	// ���ˌ��̐ݒ�
	VetexBuffer[0].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VetexBuffer[1].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VetexBuffer[2].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VetexBuffer[3].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	VetexBuffer[0].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].texturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].texturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].texturePosition = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_vertexBuffer->Unlock();


	//�I�u�W�F�N�g�̒��_�C���f�b�N�X�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
	{
		std::cout << "[Error] ���_�C���f�N�X�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
		return E_FAIL;
	}
	WORD* vertexIndex = NULL;							// �C�f�b�N�X�̒��g�𖄂߂�
	m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X �o�b�t�@�[ �������[�ւ̃|�C���^�[���擾����

	vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 3;
	vertexIndex[3] = 0, vertexIndex[4] = 3, vertexIndex[5] = 2;

	m_indexBuffer->Unlock();	// �C���f�b�N�X �f�[�^�̃��b�N����������

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
// �e�N�X�`����`�悷��(Shader)
//
//*****************************************************************************
void Plane::Draw(Shader* shader)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetVertexDeclaration(m_vertexDecl);								// ���_�錾��ݒ�
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX_3D));			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C�i��
	pDevice->SetFVF(FVF_VERTEX_3D);												// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetIndices(m_indexBuffer);											// ���_�C���f�b�N�X�o�b�t�@��ݒ�
	shader->m_effectPoint->SetTexture(shader->m_textureHandle, m_fieldTexture);	// �e�N�X�`���̐ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, NUM_POLYGON);	// �|���S���̕`��
}