//*****************************************************************************
//
// 平面処理[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

#include "Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Plane
{
private:
	D3DXVECTOR3		m_pos;	// 位置
	D3DXVECTOR3		m_rot;	// 回転
	D3DXVECTOR3		m_scl;	// 拡大縮小
	
	LPDIRECT3DVERTEXBUFFER9	m_planeVertexBuff;	// 頂点バッファへのポインタ

	HRESULT MakeVertex(int width, int height);	// 頂点作成
	HRESULT MakeVertexDT(int width, int height);	// 頂点作成(多重テクスチャ)
	//void SetTexture(LPDIRECT3DTEXTURE9* point);	// テクスチャを設定
public:
	LPDIRECT3DTEXTURE9			m_fieldTexture;	// フィールドテクスチャ

	Plane();
	~Plane();

	void InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// 座標を設定
	void InitPlaneDT(D3DXVECTOR3 pos, D3DXVECTOR2 size);	// 座標を設定(多重テクスチャ)
	void Draw();	// テクスチャを描画する
	void Draw(LPDIRECT3DTEXTURE9 texture, D3DXCONSTANT_DESC desc1, D3DXCONSTANT_DESC desc2);	// 多重テクスチャを描画する(PixelShader)
	void Draw(LPDIRECT3DTEXTURE9 texture, D3DXCONSTANT_DESC desc);	// テクスチャを描画する(PixelShader)
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);	// 臨時ーーワールド変換
};
#endif // !_PLANE_H_
