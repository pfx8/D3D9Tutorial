//*****************************************************************************
//
// �t�B�[���h����[FieldClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _FIELD_CLASS_H_
#define _FIELD_CLASS_H_

#include "Main.h"

#include "TextureManagerClass.h"



class Field
{
private:
	D3DXVECTOR3		m_pos;		// �ʒu
	D3DXVECTOR3		m_rot;		// ��]
	D3DXVECTOR3		m_scl;		// �g��k��
	
	TextureManager*			m_textureManager;	// �e�N�X�`���}�l�W�����g
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffField;	// ���_�o�b�t�@�ւ̃|�C���^

	// �Վ��ɉB��
	// std::string		m_path;				// ���f���̃p�X

public:
	Field();
	~Field();

	// ���W��ݒ�
	void InitCoordinate(D3DXVECTOR3 pos);

	// ���_�쐬
	HRESULT MakeVertex(int Width, int height);

	// �e�N�X�`����`�悷��
	void Draw();

	// �Վ��[�[���[���h�ϊ�
	void setWorldMatrix(D3DXMATRIX& mtxWorld);
};




#endif // !_FIELD_CLASS_H_
