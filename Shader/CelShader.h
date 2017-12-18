//*****************************************************************************
//
// �g�D�\���V�F�[�_�[���� [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CEL_SHADER_H_
#define _CEL_SHADER_H_

#include "../Modules/Shader.h"

class CelShader : public Shader
{
private:
	HRESULT LoadEffectFile();					// ���_�V�F�[�_�[�t�@�C����ǂݍ���
	void GetShaderTechniqueAndParameter();		// �V�F�[�_�[���g�����߂ɁA�e�ݒ������

public:
	ID3DXEffect* m_effectPoint;		// �G�t�F�N�g(���������_�����O�ۑ������)
	D3DXHANDLE	m_celShaderHandle;	// �G�t�F�N�g�̃e�N�j�b�N
	D3DXHANDLE	m_WVPMatrixHandle;	// �ϊ��s��
	D3DXHANDLE	m_lightingHandle;		// ���̕���
	D3DXHANDLE	m_changeMatrixHandle;	// �ύX�s��
	//D3DXHANDLE	m_textureHandle;		// �e�N�X�`��

	CelShader();
	~CelShader();

	void InitShader();						// �V�F�[�_�[������������
	void UpdateLight(D3DXVECTOR3 direction);	// �X�V���C�g�x�N�g��
};

#endif // !_CEL_SHADER_H_
