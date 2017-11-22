//*****************************************************************************
//
// �t�B�[���h����[Field.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _FIELD_H_
#define _FIELD_H_

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Field
{
private:
	D3DXVECTOR3		m_pos;		// �ʒu
	D3DXVECTOR3		m_rot;		// ��]
	D3DXVECTOR3		m_scl;		// �g��k��
	
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffField;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_FieldTexture;	// �t�B�[���h�e�N�X�`��

public:
	Field();
	~Field();

	// ���W��ݒ�
	void SetCoordinate(D3DXVECTOR3 pos);

	// ���_�쐬
	HRESULT MakeVertex(int Width, int height);

	// �e�N�X�`����`�悷��
	void Draw();

	// �Վ��[�[���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);

	// �e�N�X�`����ݒ�
	void Field::SetTexture(LPDIRECT3DTEXTURE9* point);
};




#endif // !_FIELD_H_
