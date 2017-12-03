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
	IDirect3DVertexShader9* m_vertexShader;		// ���_�V�F�[�_�[�|�C���^
	IDirect3DVertexDeclaration9* m_vertexDecl;	// ���_�錾
	ID3DXConstantTable* m_constTable;			// �萔�\

	D3DXHANDLE m_ScalarHandle;			// ���[�t�B���O�v�Z���鐔�l
	D3DXHANDLE m_WVPMatrixHandle;		// ���[���h�}�g���b�N�X�n���h��
	D3DXHANDLE m_LightDirectionHandle;	// �J���[�}�g���b�N�X�n���h��

	Shader();
	~Shader();

	HRESULT LoadShaderFile();				// �V�F�[�_�[�t�@�C����ǂݍ���
};

#endif // !_SHADER_H_
