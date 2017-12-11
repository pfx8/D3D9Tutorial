//*****************************************************************************
//
// Shader���� [Shader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Engine.h"

class Shader
{
private:

public:
	ID3DXEffect* m_effectPoint;	// �G�t�F�N�g(���������_�����O�ۑ������)
	
	D3DXHANDLE m_techniqueHandle;	// �G�t�F�N�g�̃e�N�j�b�N

	D3DXHANDLE m_WVPMatrixHandle;	// �ϊ��s��
	//D3DXHANDLE m_lightingHandle;	// ���̕���
	D3DXHANDLE m_textureHandle;		// �e�N�X�`��

	Shader();
	~Shader();

	HRESULT LoadEffectFile();		// ���_�V�F�[�_�[�t�@�C����ǂݍ���
};

#endif // !_SHADER_H_
