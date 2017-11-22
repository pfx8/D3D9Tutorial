//*****************************************************************************
//
// バウンディングボックス処理[BoundingBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BOUNDING_BOX_H_
#define _BOUNDING_BOX_H_

#include "Engine.h"

#include "Mesh.h"
//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class BoundingBox
{
private:
	D3DXVECTOR3	m_pos;	// バウンディングボックス座標
	D3DXVECTOR3	m_rot;	// 回転
	D3DXVECTOR3	m_scl;	// 拡大縮小

	D3DXVECTOR3	m_Size;	// バウンディングボックスサイズ
	float		m_Alpha;	// 透明度

	Mesh*		m_Mesh;	// メッシュ

	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9 m_IndexBuffer;	// インデックスバッファ

public:
	BoundingBox();
	~BoundingBox();

	// 幅、高さ、奥行き、透明度を初期化
	void InitBox(int width, int height, int depth, float alpha);

	// 長方体頂点を設定
	HRESULT MakeVertex();

	// 臨時ーーワールド変換
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);

	// バウンディングボックスを描画する
	void Draw();

	// 当たり判定
	//bool BoundingBox::CheckHitBB(Character* Object);

	// バウンディングボックスサイズを取得
	D3DXVECTOR3* GetSize();

	// バウンディングボックス位置を取得
	D3DXVECTOR3* GetPosition();
};


#endif // !_BOUNDING_BOX_H_
