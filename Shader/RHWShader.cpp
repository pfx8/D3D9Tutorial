//*****************************************************************************
//
// ��ʍ��W�p�V�F�[�_�[ [RHWShader.h]
// 
// ����:�^�C�g���ƃG���f�B���O�̕`��
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "RHWShader.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
RHWShader::RHWShader()
{
	this->effectPoint = NULL;
	this->RHWShaderHandle = NULL;
	this->textureHandle = NULL;
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
RHWShader::~RHWShader()
{
	RELEASE_POINT(this->effectPoint);
}

//*****************************************************************************
//
// �V�F�[�_�[��������
//
//*****************************************************************************
void RHWShader::InitShader()
{
	LoadEffectFile();
	GetShaderParameter();
}

//*****************************************************************************
//
// ���_�V�F�[�_�[�t�@�C����ǂݍ���
//
//*****************************************************************************
HRESULT RHWShader::LoadEffectFile()
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
						"Shader/RHWShader.fx",	// �G�t�F�N�g�t�@�C���̖��O
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effectPoint,		// �G�t�F�N�g�|�C���^
						&errorBuffer);		// �G���[���


	if (errorBuffer)	// �G���[���`�F�b�N
	{
		std::cout << "[Error] Shader/RHWShader.fx ���ǂݍ��߂Ȃ�" << std::endl;	// �G���[���b�Z�[�W
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// �G���[���b�Z�[�W
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<RHWShader> Success!" << std::endl;
	return S_OK;
}

//*****************************************************************************
//
// �V�F�[�_�[���g�����߂ɁA�e�ݒ������
//
//*****************************************************************************
void RHWShader::GetShaderParameter()
{
	// �����_�����O�̃e�N�j�b�N���擾
	this->RHWShaderHandle = this->effectPoint->GetTechniqueByName("RHWRender");

	// �V�F�[�_�[���̃O���[�o���ϐ����擾
	this->textureHandle = this->effectPoint->GetParameterByName(0, "tex");
}