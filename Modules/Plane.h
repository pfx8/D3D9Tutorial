//*****************************************************************************
//
// ���ʏ���[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

#include "../Engine.h"
#include "../Shader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Plane
{
private:
	IDirect3DVertexDeclaration9* m_vertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9	m_vertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_indexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	
	HRESULT MakeVertexDecl(int width, int height);	// ���_�錾
public:
	D3DXVECTOR3		m_pos;	// �ʒu
	D3DXVECTOR3		m_rot;	// ��]
	D3DXVECTOR3		m_scl;	// �g��k��
	LPDIRECT3DTEXTURE9			m_fieldTexture;	// �t�B�[���h�e�N�X�`��

	Plane();
	~Plane();

	void InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// ���W��ݒ�
	void Draw(Shader* shader);	// �e�N�X�`����`�悷��(PixelShader)
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);	// �Վ��[�[���[���h�ϊ�
};
#endif // !_PLANE_H_
