//*****************************************************************************
//
// �r���{�[�h���� [billboard.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BILLBOARD_H_
#define  _BILLBOARD_H_

#include "../Engine.h"

#define	TEXTURE_BILLBOARD		"data/TEXTURE/bullet000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	BILLBOARD_SIZE_X		(10.0f)							// �r���{�[�h�̕�
#define	BILLBOARD_SIZE_Y		(10.0f)							// �r���{�[�h�̍���
#define	VALUE_MOVE_BILLBOARD	(0.30f)							// �ړ����x
#define	RATE_REGIST				(0.075f)						// ��R�W��
#define	RATE_REFRECT			(-0.90f)						// ���ˌW��

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class BillBoard
{
private:
	HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);
	void SetVertexBillboard(float fSizeX, float fSizeY);

public:
	LPDIRECT3DTEXTURE9		texture;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9	vertexBuff;					// ���_�o�b�t�@

	D3DXMATRIX				worldMatrix;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3				pos;						// �ʒu
	D3DXVECTOR3				scl;						// �X�P�[��
	D3DXVECTOR3				move;						// �ړ���

	bool						g_use;

	BillBoard();
	~BillBoard();

	HRESULT InitBillboard(void);
	void UninitBillboard(void);
	void UpdateBillboard(void);
	void DrawBillboard(void);


	void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);
};

#endif // !_BILLBOARD_H_






