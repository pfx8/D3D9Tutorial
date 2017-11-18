//*****************************************************************************
//
// �o�E���f�B���O�{�b�N�X����[BoundingBoxClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BOUNDING_BOX_CLASS_H_
#define _BOUNDING_BOX_CLASS_H_

#include "Main.h"
#include "MeshClass.h"

class BoundingBox
{
private:
	D3DXVECTOR3 m_pos;	// �o�E���f�B���O�{�b�N�X���W
	D3DXVECTOR3 m_rot;	// ��]
	D3DXVECTOR3 m_scl;	// �g��k��

	Mesh* m_Mesh;	// ���b�V��

	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;				// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_IndexBuffer;				// �C���f�b�N�X�o�b�t�@
public:
	BoundingBox();
	~BoundingBox();

	// ���A�����A���s���ɂ���Ē����̂����
	HRESULT InitBox(int width, int height, int depth, float alpha);

	// �Վ��[�[���[���h�ϊ�
	void setWorldMatrix(D3DXMATRIX& mtxWorld);

	// �o�E���f�B���O�{�b�N�X��`�悷��
	void Draw();
};


#endif // !_BOUNDING_BOX_CLASS_H_
