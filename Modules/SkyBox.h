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
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9			m_vertexBuffer;	// ���_�o�b�t�@
	float							m_length;		// �{�b�N�X�̒���

public:
	D3DXMATRIX						m_worldMatrix;	// ���[���h�ϊ��}�g���b�N�X
	LPDIRECT3DTEXTURE9				m_texture[5];	// �e�N�X�`���z��
	// [0]�O [1]��� [2]�� [3]�E [4]��
	
	SkyBox();
	~SkyBox();

	HRESULT InitSkyBox(float length);	// �X�J�C�{�b�N�X��������
	void Draw(Shader *shader);	// �X�J�C�{�b�N�X��`��
};