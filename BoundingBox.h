//*****************************************************************************
//
// �o�E���f�B���O�{�b�N�X����[BoundingBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "Engine.h"

#include "Mesh.h"
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

	D3DXVECTOR3	m_Size;	// �o�E���f�B���O�{�b�N�X�T�C�Y
	float		m_Alpha;	// �����x

	Mesh*		m_Mesh;	// ���b�V��

	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_IndexBuffer;	// �C���f�b�N�X�o�b�t�@

public:
	BoundingBox();
	~BoundingBox();

	// ���A�����A���s���A�����x��������
	void InitBox(int width, int height, int depth, float alpha);

	// �����̒��_��ݒ�
	HRESULT MakeVertex();

	// �Վ��[�[���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);

	// �o�E���f�B���O�{�b�N�X��`�悷��
	void Draw();

	// �����蔻��
	//bool BoundingBox::CheckHitBB(Character* Object);

	// �o�E���f�B���O�{�b�N�X�T�C�Y���擾
	D3DXVECTOR3* GetSize();

	// �o�E���f�B���O�{�b�N�X�ʒu���擾
	D3DXVECTOR3* GetPosition();
};


#endif // !_BOUNDING_BOX_H_
