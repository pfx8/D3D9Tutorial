//*****************************************************************************
//
// バウンディングボックス処理[BoundingBox.h]
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
	D3DXVECTOR3 pos;		// 頂点座標
	D3DCOLOR	diffuse;	// 反射光
}BOUNDINGBOXVERTEX;

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class BoundingBox
{
private:
	D3DXVECTOR3						m_pos;	 // 座標
	D3DXVECTOR3						m_rot;	 // 回転
	D3DXVECTOR3						m_scl;	 // 拡大縮小
	float							m_alpha; // 透明度
	D3DXMATRIX						m_mtxWorld;		// ワールド変換行列
	LPDIRECT3DVERTEXBUFFER9			m_vertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9			m_indexBuffer;	// インデックスバッファ
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// 頂点シェーダー宣言

public:
	D3DXVECTOR3	m_size;					// バウンディングボックスサイズ
	bool		m_isBoundingBoxDraw;	// バウンディングボックスの描画チェック

	BoundingBox();
	~BoundingBox();

	HRESULT MakeVertex();											// 長方体頂点を設定
	void InitBox(int width, int height, int depth, float alpha);	// 幅、高さ、奥行き、透明度を初期化
	void SetWorldMatrix();		// ワールド変換
	void Draw();	// バウンディングボックスを描画する
};
#endif // !_BOUNDING_BOX_H_
