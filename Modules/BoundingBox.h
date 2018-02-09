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
	D3DXVECTOR3						pos;			// 座標
	D3DXVECTOR3						rot;			// 回転
	D3DXVECTOR3						scl;			// 拡大縮小
	float							alpha;			// 透明度
	D3DXMATRIX						mtxWorld;		// ワールド変換行列
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// インデックスバッファ
	IDirect3DVertexDeclaration9*	vertexDecl;	// 頂点シェーダー宣言

public:
	D3DXVECTOR3	size;				// バウンディングボックスサイズ
	bool		isBoundingBoxDraw;	// バウンディングボックスの描画チェック

	BoundingBox();
	~BoundingBox();

	HRESULT MakeVertex();											// 長方体頂点を設定
	void InitBox(int width, int height, int depth, float alpha);	// 幅、高さ、奥行き、透明度を初期化
	void SetWorldMatrix();		// ワールド変換
	void Draw();	// バウンディングボックスを描画する
};
#endif // !_BOUNDING_BOX_H_
