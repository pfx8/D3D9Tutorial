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
HRESULT Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	m_pos = pos;	// �ʒu
	MakeVertexDecl(planeSize);	// ���_�錾(shader)

	{
		//m_vertexNum = (planeNum.x + 1) * (planeNum.y + 1);	// �����_��
		//m_polygonNum = planeNum.x * planeNum.y * 2;		// �|���S����

		//LPDIRECT3DDEVICE9 pDevice = GetDevice();

		//// ���_�V�F�[�_�[�錾
		//{
		//	D3DVERTEXELEMENT9 planeDecl[] =		// ���_�f�[�^�̃��C�A�E�g���`
		//	{
		//		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		//		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		//		{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
		//		{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		//		D3DDECL_END()
		//	};
		//	pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
		//}

		//// ���_�o�b�t�@�쐬
		//{
		//	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)))
		//	{
		//		std::cout << "[Error] ���_�o�b�t�@�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
		//		return E_FAIL;
		//	}

		//	VERTEX_3D* VertexBuffer;

		//	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
		//	m_vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

		//	// ���_�o�b�t�@�̒��g�𖄂߂�
		//	// ���_���W(���[�J�����W = �`���`�����Ă�)
		//	// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
		//	// m_posFiled�͐��E�ł̈ʒu��

		//	for (int numY = 0; numY < (planeNum.y + 1); numY++)
		//	{
		//		for (int numX = 0; numX < (planeNum.x + 1); numX++)
		//		{
		//			// ���_���W�̐ݒ�
		//			VertexBuffer[numY * (numX + 1) + numX].position.x = -(planeNum.x / 2.0f) * planeSize.x + numX * planeSize.x;
		//			VertexBuffer[numY * (numX + 1) + numX].position.y = 0.0f;
		//			VertexBuffer[numY * (numX + 1) + numX].position.z = (planeNum.y / 2) * planeSize.y - numY * planeSize.y;
		//			// �@���x�N�g���̐ݒ�
		//			VertexBuffer[numY * (numX + 1) + numX].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		//			// ���ˌ��̐ݒ�
		//			VertexBuffer[numY * (numX + 1) + numX].diffuse	= D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
		//			// �e�N�X�`�����W�̐ݒ�
		//			VertexBuffer[numY * (numX + 1) + numX].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
		//		}
		//	}

		//	// ���_�f�[�^���A�����b�N����
		//	m_vertexBuffer->Unlock();
		//}


		//// ���_�C���f�b�N�X�o�b�t�@�쐬
		//{
		//	if (FAILED(pDevice->CreateIndexBuffer(m_polygonNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
		//	{
		//		std::cout << "[Error] ���_�C���f�N�X�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
		//		return E_FAIL;
		//	}
		//	WORD* vertexIndex = NULL;		// �C�f�b�N�X�̒��g�𖄂߂�
		//	m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X �o�b�t�@�[ �������[�ւ̃|�C���^�[���擾����

		//	for (int numY = 0; numY < planeNum.y ; numY++)
		//	{

		//	}
		//	vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 3;
		//	vertexIndex[3] = 0, vertexIndex[4] = 3, vertexIndex[5] = 2;

		//	m_indexBuffer->Unlock();	// �C���f�b�N�X �f�[�^�̃��b�N����������
		//}
	}

	return S_OK;
}

//*****************************************************************************
//
// ���_�錾(Shader)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDecl(D3DXVECTOR2 planePos)
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
	VERTEX_3D* VertexBuffer;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
	m_vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

	// ���_�o�b�t�@�̒��g�𖄂߂�
	// ���_���W(���[�J�����W = �`���`�����Ă�)
	// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
	// m_posFiled�͐��E�ł̈ʒu��

	// ���_���W�̐ݒ�
	VertexBuffer[0].position = D3DXVECTOR3(-10, 0.0f,  10);
	VertexBuffer[1].position = D3DXVECTOR3( 10, 0.0f,  10);
	VertexBuffer[2].position = D3DXVECTOR3(-10, 0.0f, -10);
	VertexBuffer[3].position = D3DXVECTOR3( 10, 0.0f, -10);

	// �@���x�N�g���̐ݒ�
	VertexBuffer[0].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VertexBuffer[1].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VertexBuffer[2].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VertexBuffer[3].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	// ���ˌ��̐ݒ�
	VertexBuffer[0].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VertexBuffer[1].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VertexBuffer[2].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VertexBuffer[3].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	VertexBuffer[0].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VertexBuffer[1].texturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VertexBuffer[2].texturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VertexBuffer[3].texturePosition = D3DXVECTOR2(1.0f, 1.0f);


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
	pDevice->SetFVF(FVF_VERTEX_3D);											// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetIndices(m_indexBuffer);										// ���_�C���f�b�N�X�o�b�t�@��ݒ�
	shader->m_effectPoint->SetTexture(shader->m_textureHandle, m_fieldTexture);	// �e�N�X�`���̐ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, NUM_POLYGON);	// �|���S���̕`��
}