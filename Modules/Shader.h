//*****************************************************************************
//
// �g�D�\���V�F�[�_�[���� [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "../Engine.h"

class Shader
{
private:
	virtual HRESULT LoadEffectFile();		// ���_�V�F�[�_�[�t�@�C����ǂݍ���
	virtual void GetShaderParameter();		// �V�F�[�_�[���̕ϐ����擾

public:
	ID3DXEffect* m_effectPoint;		// �G�t�F�N�g(���������_�����O�ۑ������)

	D3DXHANDLE   m_shaderHandle;	// �G�t�F�N�g�̃e�N�j�b�N
	D3DXHANDLE   m_WMatrixHandle;	// ���[���h�ϊ��s��
	D3DXHANDLE   m_VPMatrixHandle;	// �r���[�C���O�ϊ��ƃv���W�F�N�V�����ϊ��s��
	D3DXHANDLE   m_textureHandle;	// �e�N�X�`��
	D3DXHANDLE   m_alphaHandle;		// �J���[�̃A���t�@�l

	Shader();
	~Shader();

	void InitShader();				// �V�F�[�_�[������������
};

#endif // !_SHADER_H_
