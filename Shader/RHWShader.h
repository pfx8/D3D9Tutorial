//*****************************************************************************
//
// ��ʍ��W�p�V�F�[�_�[ [RHWShader.h]
// 
// ����:�^�C�g���ƃG���f�B���O�̕`��
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RHW_SHADER_H_
#define _RHW_SHADER_H_

#include "../Modules/Shader.h"

class RHWShader : public Shader
{
private:
	HRESULT LoadEffectFile();		// ���_�V�F�[�_�[�t�@�C����ǂݍ���
	void GetShaderParameter();		// �V�F�[�_�[���g�����߂ɁA�e�ݒ������

public:
	ID3DXEffect*	effectPoint;		// �G�t�F�N�g(���������_�����O�ۑ������)
	D3DXHANDLE		RHWShaderHandle;	// �G�t�F�N�g�̃e�N�j�b�N
	D3DXHANDLE		textureHandle;	// �e�N�X�`��

	RHWShader();
	~RHWShader();

	void InitShader();	// �V�F�[�_�[������������
};

#endif // !_RHW_SHADER_H_
