//*****************************************************************************
//
// Shader���� [Shader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Shader.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
Shader::Shader()
{
	m_vertexShader = NULL;
	m_vertexDecl = NULL;
	m_constTable = NULL;

	m_WVPMatrixHandle = NULL;
	m_LightDirectionHandle = NULL;
	m_ScalarHandle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_vertexShader);
	RELEASE_POINT(m_vertexDecl);
	RELEASE_POINT(m_constTable);

}

//*****************************************************************************
//
// �V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT Shader::LoadShaderFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ID3DXBuffer* shaderBuffer = NULL;	// �V�F�[�_�[�o�b�t�@
	ID3DXBuffer* errorBuffer = NULL;	// �G���[�o�b�t�@

	D3DVERTEXELEMENT9 MorphMeshDecl[] =
	{
		// �X�g���[���ԍ�1
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },

		// �X�g���[���ԍ�2
		{ 1,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
		{ 1, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   1 },
		D3DDECL_END()
	};

	HRESULT hr = D3DXCompileShaderFromFile(
		"Shader/Vertex.hlsl",
		0,
		0,
		"SetVertex",		// �V�F�[�_�[�̓�����֐�
		"vs_1_1",			// �R���p�C�� �^�[�Q�b�g���܂ޕ�����ւ̃|�C���^???
		D3DXSHADER_DEBUG,	// ���p�C�� �I�v�V����
		&shaderBuffer,	// �V�F�[�_�[�o�b�t�@
		&errorBuffer,		// �G���[�o�b�t�@
		&m_constTable);	// �萔�\
	
	if (FAILED(hr))	// �G���[���`�F�b�N
	{
		std::cout << "Error: Shader->LoadShader" << std::endl;
		return E_FAIL;
	}

	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "Error: Shader->errorBuffer" << std::endl;
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}


	pDevice->CreateVertexShader((DWORD*)shaderBuffer->GetBufferPointer(), &m_vertexShader);	// ���_�V�F�[�_�[���쐬����
	pDevice->CreateVertexDeclaration(MorphMeshDecl, &m_vertexDecl);	// �f�o�C�X����ђ��_�v�f���璸�_�V�F�[�_�錾���쐬����
	RELEASE_POINT(shaderBuffer);	// �V�F�[�_�[�o�b�t�@�������[�X

	// �V�F�[�_�[�t�@�C�����̕ϐ����擾
	m_WVPMatrixHandle = m_constTable->GetConstantByName(0, "WVPMatrix");	// WVP�}�g���b�N�X
	m_LightDirectionHandle = m_constTable->GetConstantByName(0, "LightDirection");	// �����ˌ�
	m_ScalarHandle = m_constTable->GetConstantByName(0, "Scalar");	// ���[�t�B���O���l

	m_constTable->SetVector(pDevice, m_LightDirectionHandle, &D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f));
	m_constTable->SetDefaults(pDevice);	// �f�t�H���g�ݒ�

	return S_OK;
}