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
	m_pixelShader = NULL;
	m_constTable = NULL;

	m_ratioHandle = NULL;
	m_samp0Handle = NULL;
	m_samp1Handle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_pixelShader);
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

	// �s�N�Z�����[�h�`�F�b�N
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* shaderBuffer = NULL;	// �V�F�[�_�[�o�b�t�@
	ID3DXBuffer* errorBuffer = NULL;	// �G���[�o�b�t�@

	D3DXCompileShaderFromFile(
		"Shader/PixelShader.hlsl",	//�V�F�[�_�[�t�@�C���p�X
		0,				// �f�t�H���g�ݒ�
		0,				// �f�t�H���g�ݒ�
		"Main",			// �V�F�[�_�[�̓�����֐�
		"ps_2_0",			// �R���p�C���^�[�Q�b�g���܂ޕ�����ւ̃|�C���^
		D3DXSHADER_DEBUG,	// ���p�C�� �I�v�V����
		&shaderBuffer,	// �V�F�[�_�[�o�b�t�@
		&errorBuffer,		// �G���[�o�b�t�@
		&m_constTable);	// �萔�\

	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] �V�F�[�_�[���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	// �s�N�Z���V�F�[�_�[�����
	pDevice->CreatePixelShader((DWORD*)shaderBuffer->GetBufferPointer(), &m_pixelShader);

	// �V�F�[�_�[�t�@�C�����̕ϐ����擾
	m_ratioHandle = m_constTable->GetConstantByName(0, "Scalar");	// ������䗦
	m_samp0Handle = m_constTable->GetConstantByName(0, "Samp0");	// �T���v���[0
	m_samp1Handle = m_constTable->GetConstantByName(0, "Samp1");	// �T���v���[1

	//
	UINT count;
	m_constTable->GetConstantDesc(m_samp0Handle, &m_samp0Desc, &count);	// 
	m_constTable->GetConstantDesc(m_samp1Handle, &m_samp1Desc, &count);	// 

	m_constTable->SetDefaults(pDevice);	// �f�t�H���g�ݒ�

	return S_OK;
}