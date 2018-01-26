//*****************************************************************************
//
// �X�J�C�{�b�N�X���� [SkyBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#include "Shader.h"
#include "..\Engine.h"

typedef struct SKYBOXVERTEX
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR2 uv;		// UV���W
}SKYBOXVERTEX;

#define FVF_SKYBOX (D3DFVF_XYZ | D3DFVF_TEX1)

class SkyBox
{
private:
	D3DXVECTOR3						m_pos;			// ���W
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9			m_vertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			m_indexBuffer;	// �C���f�b�N�X�o�b�t�@
	D3DXMATRIX						m_mtxWorld;		// ���[���h�ϊ��s��
	float							m_length;		// �{�b�N�X�̒���

public:
	D3DXMATRIX						m_worldMatrix;	// ���[���h�ϊ��}�g���b�N�X
	LPDIRECT3DTEXTURE9				m_texture;	// �e�N�X�`���z��
	
	SkyBox();
	~SkyBox();

	HRESULT InitSkyBox(float length);			// �X�J�C�{�b�N�X��������
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);	// �Վ��[�[���[���h�ϊ�
	void Draw(Shader *shader);					// �X�J�C�{�b�N�X��`��
};