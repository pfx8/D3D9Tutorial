//*****************************************************************************
//
// ���ʏ���[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Plane
{
private:
	D3DXVECTOR3		m_pos;	// �ʒu
	D3DXVECTOR3		m_rot;	// ��]
	D3DXVECTOR3		m_scl;	// �g��k��
	
	LPDIRECT3DVERTEXBUFFER9	m_planeVertexBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	HRESULT MakeVertex(int width, int height);	// ���_�쐬
	HRESULT MakeVertexDT(int width, int height);	// ���_�쐬(���d�e�N�X�`��)
	//void SetTexture(LPDIRECT3DTEXTURE9* point);	// �e�N�X�`����ݒ�
public:
	LPDIRECT3DTEXTURE9			m_fieldTexture;	// �t�B�[���h�e�N�X�`��

	Plane();
	~Plane();

	void InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// ���W��ݒ�
	void InitPlaneDT(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// ���W��ݒ�(���d�e�N�X�`��)
	void Draw();	// �e�N�X�`����`�悷��
	void Draw(LPDIRECT3DTEXTURE9 texture, D3DXCONSTANT_DESC desc1, D3DXCONSTANT_DESC desc2);	// ���d�e�N�X�`����`�悷��(PixelShader)
	void Draw(LPDIRECT3DTEXTURE9 texture, D3DXCONSTANT_DESC desc);	// �e�N�X�`����`�悷��(PixelShader)
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);	// �Վ��[�[���[���h�ϊ�
};
#endif // !_PLANE_H_
