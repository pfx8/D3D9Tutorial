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
	m_effectPoint = NULL;
	
	m_WVPMatrixHandle = NULL;
	m_lightingHandle = NULL;
	m_techniqueHandle = NULL;
	m_textureHandle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_effectPoint);
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT Shader::LoadEffectFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �s�N�Z���@�\�`�F�b�N
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* errorBuffer = NULL;	// �G���[�o�b�t�@

	D3DXCreateEffectFromFile(pDevice,
						"Effect.txt",	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&m_effectPoint,	// �G�t�F�N�g�|�C���^
						&errorBuffer);	// �G���[���


	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] �G�t�F�N�g���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	// �G�t�F�N�g�̃e�N�j�b�N��ݒ�
	m_techniqueHandle = m_effectPoint->GetTechniqueByName("T0");

	// �V�F�[�_�[���̃O���[�o���ϐ����擾
	m_WVPMatrixHandle = m_effectPoint->GetParameterByName(0, "WVPMatrix");
	m_lightingHandle = m_effectPoint->GetParameterByName(0, "LightDirection");
	m_textureHandle = m_effectPoint->GetParameterByName(0, "Tex");

	return S_OK;
}