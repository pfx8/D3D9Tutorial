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
	ID3DXBuffer* m_shaderBuffer;			// �V�F�[�_�[�o�b�t�@
	ID3DXBuffer* m_errorBuffer;				// �G���[�o�b�t�@
	IDirect3DVertexShader9* m_vertexShader;	// ���_�V�F�[�_�[�|�C���^
	ID3DXConstantTable* m_constTable;		// �萔�\
	D3DXHANDLE m_WVPMatrixHandle;			// ���[���h�}�g���b�N�X�n���h��
	D3DXHANDLE m_colorHandle;				// �J���[�}�g���b�N�X�n���h��

	Shader();
	~Shader();

	HRESULT LoadShaderFile();				// �V�F�[�_�[�t�@�C����ǂݍ���
};

#endif // !_SHADER_H_
