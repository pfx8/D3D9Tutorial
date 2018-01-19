//*****************************************************************************
//
// �X�J�C�{�b�N�X���� [SkyBox.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SkyBox.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
SkyBox::SkyBox()
{
	// ������
	m_vertexBuffer = NULL;
	for (int count = 0; count < 5; count++)
	{
		m_texture[count] = NULL;
	}
	m_length = 0.0f;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
SkyBox::~SkyBox()
{
	RELEASE_POINT(m_vertexBuffer);
	for (int count = 0; count < 5; count++)
	{
		RELEASE_POINT(m_texture[count]);
	}
}

//*****************************************************************************
//
// �X�J�C�{�b�N�X��������
//
//*****************************************************************************
HRESULT SkyBox::InitSkyBox(float length)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	m_length = length;
	
	// ���_�V�F�[�_�[�錾
	{
		D3DVERTEXELEMENT9 planeDecl[] =		// ���_�f�[�^�̃��C�A�E�g���`
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
			{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		device->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
	}

	//���_�o�b�t�@���쐬
	if (FAILED(device->CreateVertexBuffer(20 * sizeof(SKYBOXVERTEX), 0,
		FVF_SKYBOX, D3DPOOL_MANAGED, &m_vertexBuffer, 0)))
	{
		std::cout << "[Error] ���_�o�b�t�@�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
		return E_FAIL;
	}

	// ���_�o�b�t�@�̒��g�𖄂߂�
	SKYBOXVERTEX vertices[] =
	{
		// �O
		{ {-m_length / 2, 0.0f,			m_length / 2}, {0.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2,	m_length / 2}, {0.0f, 0.0f} },
		{ { m_length / 2, 0.0f,         m_length / 2}, {1.0f, 1.0f} },
		{ { m_length / 2, m_length / 2, m_length / 2}, {1.0f, 0.0f} },

		// ���
		{ { m_length / 2, 0.0f,         -m_length / 2}, {0.0f, 1.0f} },
		{ { m_length / 2, m_length / 2, -m_length / 2}, {0.0f, 0.0f} },
		{ {-m_length / 2, 0.0f,         -m_length / 2}, {1.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2, -m_length / 2}, {1.0f, 0.0f} },

		// ��
		{ {-m_length / 2, 0.0f,         -m_length / 2}, {0.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2, -m_length / 2}, {0.0f, 0.0f} },
		{ {-m_length / 2, 0.0f,          m_length / 2}, {1.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2,  m_length / 2}, {1.0f, 0.0f} },

		// �E
		{ {m_length / 2, 0.0f,          m_length / 2}, {0.0f, 1.0f} },
		{ {m_length / 2, m_length / 2,  m_length / 2}, {0.0f, 0.0f} },
		{ {m_length / 2, 0.0f,         -m_length / 2}, {1.0f, 1.0f} },
		{ {m_length / 2, m_length / 2, -m_length / 2}, {1.0f, 0.0f} },

		// ��
		{ {m_length / 2,  m_length / 2, -m_length / 2}, {1.0f, 0.0f} },
		{ {m_length / 2,  m_length / 2,  m_length / 2}, {1.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2, -m_length / 2}, {0.0f, 0.0f} },
		{ {-m_length / 2, m_length / 2,  m_length / 2}, {0.0f, 1.0f} },

	};

	void* pVertices;
	m_vertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	// ���_�\���̂̃f�[�^�𒸓_�o�b�t�@�ɃR�s�[
	memcpy(pVertices, vertices, sizeof(vertices));
	m_vertexBuffer->Unlock();
}

//*****************************************************************************
//
// �X�J�C�{�b�N�X��`��
//
//*****************************************************************************
void SkyBox::Draw(Shader *shader)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetVertexDeclaration(m_vertexDecl);							// ���_�錾��ݒ�
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(SKYBOXVERTEX));	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C�i��
	pDevice->SetFVF(FVF_SKYBOX);											// ���_�t�H�[�}�b�g�̐ݒ�

	// �`��
	for (int count = 0; count < 5; count++)
	{
		shader->m_effectPoint->SetTexture(shader->m_texture1Handle, m_texture[count]);	// �e�N�X�`���̐ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, count * 4, 2);
	}
}