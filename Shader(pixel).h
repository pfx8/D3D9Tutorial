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
	LPDIRECT3DPIXELSHADER9 m_pixelShader;	// �s�N�Z���V�F�[�_�[�|�C���^
	ID3DXConstantTable* m_constTable;		// �萔�\
	LPDIRECT3DVERTEXSHADER9 m_vertexShader;	// ���_�V�F�[�_�[
	
	D3DXHANDLE m_ratioHandle;	// ������䗦
	D3DXHANDLE m_samp0Handle;	// �T���v���[0
	D3DXHANDLE m_samp1Handle;	// �T���v���[1
	D3DXHANDLE m_lightingHandle;	// ������

	D3DXCONSTANT_DESC m_samp0Desc;	// �T���v���[�萔�e�[�u��
	D3DXCONSTANT_DESC m_samp1Desc;	// �T���v���[�萔�e�[�u��

	Shader();
	~Shader();

	HRESULT LoadShaderFile();				// �V�F�[�_�[�t�@�C����ǂݍ���
};

#endif // !_SHADER_H_
