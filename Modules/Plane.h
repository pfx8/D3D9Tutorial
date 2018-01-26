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

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Plane
{
private:
	int				m_scala;

public:
	float			m_waveAngle;
	D3DXMATRIX		m_worldMatrix;	// ���[���h�ϊ��}�g���b�N�X
	D3DXVECTOR3		m_pos;	// �ʒu
	//D3DXVECTOR3		m_rot;	// ��]
	//D3DXVECTOR3		m_scl;	// �g��k��
	D3DXVECTOR2		m_planeSize;
	D3DXVECTOR2		m_planeNum;
	int				m_vertexNum;		// ���_��
	int				m_polygonNum;	// �|���S����
	int				m_indexNum;		// �C���f�b�N�X��

	IDirect3DVertexDeclaration9*m_vertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9			m_texture;	// �t�B�[���h�e�N�X�`��

	Plane();
	~Plane();

	virtual HRESULT MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// ���_�錾
	virtual HRESULT InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// ���W��ݒ�
	virtual void Draw();				// �e�N�X�`����`�悷��(PixelShader)
	void SetWorldMatrix();	// �Վ��[�[���[���h�ϊ�
	void Update();
};
#endif // !_PLANE_H_
