//*****************************************************************************
//
// �o�E���f�B���O�{�b�N�X����[BoundingBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "../Engine.h"
#include "../Shader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class BoundingBox
{
private:
	D3DXVECTOR3	m_pos;	// �o�E���f�B���O�{�b�N�X���W
	D3DXVECTOR3	m_rot;	// ��]
	D3DXVECTOR3	m_scl;	// �g��k��
	float		m_alpha;	// �����x

	LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_indexBuffer;	// �C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9* m_vertexDecl;	// ���_�V�F�[�_�[�錾

public:
	D3DXVECTOR3	m_size;	// �o�E���f�B���O�{�b�N�X�T�C�Y
	bool		m_isBoundingBoxDraw;	// �o�E���f�B���O�{�b�N�X�̕`��`�F�b�N

	BoundingBox();
	~BoundingBox();

	void InitBox(int width, int height, int depth, float alpha);	// ���A�����A���s���A�����x��������
	HRESULT MakeVertex();											// �����̒��_��ݒ�
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);						// �Վ��[�[���[���h�ϊ�
	void Draw(Shader* shader);													// �o�E���f�B���O�{�b�N�X��`�悷��

	// �����蔻��
	/*bool BoundingBox::CheckHitBB(Character* Object);*/
};


#endif // !_BOUNDING_BOX_H_
