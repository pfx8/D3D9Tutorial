//*****************************************************************************
//
// フィールド処理[Field.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _FIELD_H_
#define _FIELD_H_

#include "Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Field
{
private:
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小
	
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffField;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9			m_FieldTexture;	// フィールドテクスチャ

public:
	Field();
	~Field();

	// 座標を設定
	void SetCoordinate(D3DXVECTOR3 pos);

	// 頂点作成
	HRESULT MakeVertex(int Width, int height);

	// テクスチャを描画する
	void Draw();

	// 臨時ーーワールド変換
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);

	// テクスチャを設定
	void Field::SetTexture(LPDIRECT3DTEXTURE9* point);
};




#endif // !_FIELD_H_
