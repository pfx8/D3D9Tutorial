//*****************************************************************************
//
// ビルボード処理 [billboard.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BILLBOARD_H_
#define  _BILLBOARD_H_

#include "../Engine.h"

#define	TEXTURE_BILLBOARD		"data/TEXTURE/bullet000.png"	// 読み込むテクスチャファイル名
#define	BILLBOARD_SIZE_X		(10.0f)							// ビルボードの幅
#define	BILLBOARD_SIZE_Y		(10.0f)							// ビルボードの高さ
#define	VALUE_MOVE_BILLBOARD	(0.30f)							// 移動速度
#define	RATE_REGIST				(0.075f)						// 抵抗係数
#define	RATE_REFRECT			(-0.90f)						// 反射係数

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class BillBoard
{
private:
	HRESULT MakeVertexBillboard(LPDIRECT3DDEVICE9 pDevice);
	void SetVertexBillboard(float fSizeX, float fSizeY);

public:
	LPDIRECT3DTEXTURE9		texture;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9	vertexBuff;					// 頂点バッファ

	D3DXMATRIX				worldMatrix;				// ワールドマトリックス
	D3DXVECTOR3				pos;						// 位置
	D3DXVECTOR3				scl;						// スケール
	D3DXVECTOR3				move;						// 移動量

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






