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
	m_shaderBuffer = NULL;
	m_errorBuffer = NULL;
	m_vertexShader = NULL;
	m_constTable = NULL;

	m_WVPMatrixHandle = NULL;
	m_colorHandle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Shader::~Shader()
{
	SAFE_RELEASE_POINT(m_shaderBuffer);
	SAFE_RELEASE_POINT(m_errorBuffer);
	SAFE_RELEASE_POINT(m_vertexShader);
	SAFE_RELEASE_POINT(m_constTable);
}

//*****************************************************************************
//
// �V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT Shader::LoadShaderFile()
{
	HRESULT hr = D3DXCompileShaderFromFile(
		"Shader/Basic.hlsl",
		0,
		0,
		"SetColor",		// �V�F�[�_�[�̓�����֐�
		"vs_1_0",			// �R���p�C�� �^�[�Q�b�g���܂ޕ�����ւ̃|�C���^???
		D3DXSHADER_DEBUG,	// ���p�C�� �I�v�V����
		&m_shaderBuffer,	// �V�F�[�_�[�o�b�t�@
		&m_errorBuffer,	// �G���[�o�b�t�@
		&m_constTable);	// �萔�\

	if (m_errorBuffer)		// �G���[���o��
	{
		std::cout << "Error: Shader->m_errorBuffer" << std::endl;
		SAFE_RELEASE_POINT(m_errorBuffer);
		return E_FAIL;
	}

	if (FAILED(hr))	// �G���[���o��
	{
		std::cout << "Error: Shader->LoadShader" << std::endl;
		return E_FAIL;
	}

	// ���_�V�F�[�_�[���ł���
	hr = GetDevice()->CreateVertexShader((DWORD*)m_shaderBuffer->GetBufferPointer(), &m_vertexShader);

	if (FAILED(hr))	// �G���[���o��
	{
		std::cout << "Error: Shader->CreateVertexShader" << std::endl;
		return E_FAIL;
	}

	SAFE_RELEASE_POINT(m_shaderBuffer);	// �V�F�[�_�[�o�b�t�@�������[�X

	// �V�F�[�_�[�t�@�C�����̕ϐ����擾
	m_WVPMatrixHandle = m_constTable->GetConstantByName(0, "WVPMatrix");	// WVP�}�g���b�N�X
	m_colorHandle = m_constTable->GetConstantByName(0, "color");		// ���_�J���[

	m_constTable->SetDefaults(GetDevice());	// �f�t�H���g�ݒ�

	return S_OK;
}