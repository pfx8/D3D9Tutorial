//*****************************************************************************
//
// �X�J�C�{�b�N�X���� [SkyBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "Shader.h"
#include "..\Engine.h"

typedef struct SKYBOXVERTEX
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR2 uv;		// UV���W
}SKYBOXVERTEX;

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
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
	LPDIRECT3DTEXTURE9				m_texture;		// �e�N�X�`���z��
	
	SkyBox();
	~SkyBox();

	HRESULT InitSkyBox(float length);		// �X�J�C�{�b�N�X��������
	void SetWorldMatrix();					// �Վ��[�[���[���h�ϊ�
	void Draw();							// �X�J�C�{�b�N�X��`��
};

#endif // !_SKY_BOX_H_