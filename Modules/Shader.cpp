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
	
	m_WMatrixHandle = NULL;
	m_VPMatrixHandle = NULL;
	m_shaderHandle = NULL;
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
// �V�F�[�_�[��������
//
//*****************************************************************************
void Shader::InitShader()
{
	LoadEffectFile();
	GetShaderParameter();
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT Shader::LoadEffectFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// �s�N�Z���@�\�`�F�b�N
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* errorBuffer = NULL;		// �G���[�o�b�t�@
	D3DXCreateEffectFromFile(pDevice,
						"Shader/BasicShader.fx",	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&m_effectPoint,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���


	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] Shader/BasicShader.fx ���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<BasicShader> Success!" << std::endl;

	return S_OK;
}

//*****************************************************************************
//
// �V�F�[�_�[���̕ϐ����擾
//
//*****************************************************************************
void Shader::GetShaderParameter()
{
	m_WMatrixHandle  = m_effectPoint->GetParameterByName(0, "WMatrix");
	m_VPMatrixHandle = m_effectPoint->GetParameterByName(0, "VPMatrix");
	m_textureHandle  = m_effectPoint->GetParameterByName(0, "tex");
	m_alphaHandle    = m_effectPoint->GetParameterByName(0, "alpha");
}