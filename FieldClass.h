//*****************************************************************************
//
// フィールド処理[FieldClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _FIELD_CLASS_H_
#define _FIELD_CLASS_H_

#include "Main.h"

#include "TextureManagerClass.h"



class Field
{
private:
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小
	
	TextureManager*			m_textureManager;	// テクスチャマネジメント
	LPDIRECT3DVERTEXBUFFER9	m_VertexBuffField;	// 頂点バッファへのポインタ

	// 臨時に隠す
	// std::string		m_path;				// モデルのパス

public:
	Field();
	~Field();

	// 座標を設定
	void InitCoordinate(D3DXVECTOR3 pos);

	// 頂点作成
	HRESULT MakeVertex(int Width, int height);

	// テクスチャを描画する
	void Draw();

	// 臨時ーーワールド変換
	void setWorldMatrix(D3DXMATRIX& mtxWorld);
};




#endif // !_FIELD_CLASS_H_
