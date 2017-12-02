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
	D3DXVECTOR3		m_pos;	// �ʒu
	D3DXVECTOR3		m_rot;	// ��]
	D3DXVECTOR3		m_scl;	// �g��k��
	
	LPDIRECT3DVERTEXBUFFER9	m_vertexBuffField;	// ���_�o�b�t�@�ւ̃|�C���^

	HRESULT MakeVertex(int width, int height);	// ���_�쐬
	void SetTexture(LPDIRECT3DTEXTURE9* point);	// �e�N�X�`����ݒ�
public:
	LPDIRECT3DTEXTURE9			m_fieldTexture;	// �t�B�[���h�e�N�X�`��

	Field();
	~Field();

	// ���W��ݒ�
	void InitField(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	// �e�N�X�`����`�悷��
	void Draw();

	// �Վ��[�[���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);


};




#endif // !_FIELD_H_
