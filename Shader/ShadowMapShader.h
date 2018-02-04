//*****************************************************************************
//
// �V���h�[�V�F�[�_�[[ShadowMapShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADOW_MAP_SHADER_H_
#define _SHADOW_MAP_SHADER_H_

#include "../Modules/Shader.h"

class ShadowMapShader : public Shader
{
private:
	HRESULT LoadEffectFile();		// ���_�V�F�[�_�[�t�@�C����ǂݍ���

public:
	ID3DXEffect*		m_effectPoint;				// �G�t�F�N�g(���������_�����O�ۑ������)
	LPDIRECT3DTEXTURE9	m_shadowMapTex;		// �V���h�[�}�b�v
	D3DXHANDLE			m_shadeowMapShaderHandle;	// �G�t�F�N�g�̃e�N�j�b�N

	ShadowMapShader();
	~ShadowMapShader();

	HRESULT InitShader();	// �V�F�[�_�[������������
};

#endif // !_SHADOW_MAP_SHADER_H_
