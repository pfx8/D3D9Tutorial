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
	D3DXVECTOR3		m_pos;	// 位置
	D3DXVECTOR3		m_rot;	// 回転
	D3DXVECTOR3		m_scl;	// 拡大縮小
	
	LPDIRECT3DVERTEXBUFFER9	m_vertexBuffField;	// 頂点バッファへのポインタ

	HRESULT MakeVertex(int width, int height);	// 頂点作成
	void SetTexture(LPDIRECT3DTEXTURE9* point);	// テクスチャを設定
public:
	LPDIRECT3DTEXTURE9			m_fieldTexture;	// フィールドテクスチャ

	Field();
	~Field();

	// 座標を設定
	void InitField(D3DXVECTOR3 pos, D3DXVECTOR2 size);

	// テクスチャを描画する
	void Draw();

	// 臨時ーーワールド変換
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);


};




#endif // !_FIELD_H_
