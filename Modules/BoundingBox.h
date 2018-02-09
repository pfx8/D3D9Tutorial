//*****************************************************************************
//
// �o�E���f�B���O�{�b�N�X����[BoundingBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "Shader.h"
#include "../Engine.h"

typedef struct BOUNDINGBOXVERTEX
{
	D3DXVECTOR3 pos;		// ���_���W
	D3DCOLOR	diffuse;	// ���ˌ�
}BOUNDINGBOXVERTEX;

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class BoundingBox
{
private:
	D3DXVECTOR3						pos;			// ���W
	D3DXVECTOR3						rot;			// ��]
	D3DXVECTOR3						scl;			// �g��k��
	float							alpha;			// �����x
	D3DXMATRIX						mtxWorld;		// ���[���h�ϊ��s��
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// �C���f�b�N�X�o�b�t�@
	IDirect3DVertexDeclaration9*	vertexDecl;	// ���_�V�F�[�_�[�錾

public:
	D3DXVECTOR3	size;				// �o�E���f�B���O�{�b�N�X�T�C�Y
	bool		isBoundingBoxDraw;	// �o�E���f�B���O�{�b�N�X�̕`��`�F�b�N

	BoundingBox();
	~BoundingBox();

	HRESULT MakeVertex();											// �����̒��_��ݒ�
	void InitBox(int width, int height, int depth, float alpha);	// ���A�����A���s���A�����x��������
	void SetWorldMatrix();		// ���[���h�ϊ�
	void Draw();	// �o�E���f�B���O�{�b�N�X��`�悷��
};
#endif // !_BOUNDING_BOX_H_
