//*****************************************************************************
//
// �g�D�\���V�F�[�_�[���� [CelShader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "CelShader.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
CelShader::CelShader()
{
	m_effectPoint = NULL;
	m_celShaderHandle = NULL;
	m_WVPMatrixHandle = NULL;
	m_lightingHandle = NULL;
	//m_textureHandle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
CelShader::~CelShader()
{
	RELEASE_POINT(m_effectPoint);
}

//*****************************************************************************
//
// �V�F�[�_�[��������
//
//*****************************************************************************
void CelShader::InitShader()
{
	LoadEffectFile();
	GetShaderTechniqueAndParameter();
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT CelShader::LoadEffectFile()
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
						"Shader/CelShader.fx",	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&m_effectPoint,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���


	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] Shader/CelShader.fx ���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<CelShader> Success!" << std::endl;
	return S_OK;
}

//*****************************************************************************
//
// �X�V���C�g�x�N�g��
//
//*****************************************************************************
void CelShader::UpdateLight(D3DXVECTOR3 direction)
{
	D3DXVECTOR4 tempLight = D3DXVECTOR4(direction.x, direction.y, direction.z, 1.0f);
	m_effectPoint->SetVector(m_lightingHandle, &tempLight);
}

//*****************************************************************************
//
// �V�F�[�_�[���g�����߂ɁA�e�ݒ������
//
//*****************************************************************************
void CelShader::GetShaderTechniqueAndParameter()
{
	// �����_�����O�̃e�N�j�b�N���擾
	m_celShaderHandle = m_effectPoint->GetTechniqueByName("CelShader");
	m_outLineHandle = m_effectPoint->GetTechniqueByName("Outline");

	// �V�F�[�_�[���̃O���[�o���ϐ����擾
	m_WVPMatrixHandle = m_effectPoint->GetParameterByName(0, "WVPMatrix");
	m_lightingHandle = m_effectPoint->GetParameterByName(0, "LightDirection");
	m_typeHandle = m_effectPoint->GetParameterByName(0, "type");
	//m_textureHandle = m_effectPoint->GetParameterByName(0, "Tex");

}