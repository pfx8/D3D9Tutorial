//*****************************************************************************
//
// バウンディングボックス処理[BoundingBoxClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BOUNDING_BOX_CLASS_H_
#define _BOUNDING_BOX_CLASS_H_

#include "Main.h"
#include "MeshClass.h"

class BoundingBox
{
private:
	D3DXVECTOR3 m_pos;	// バウンディングボックス座標
	D3DXVECTOR3 m_rot;	// 回転
	D3DXVECTOR3 m_scl;	// 拡大縮小

	Mesh* m_Mesh;	// メッシュ

	LPDIRECT3DVERTEXBUFFER9 m_VertexBuffer;				// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9 m_IndexBuffer;				// インデックスバッファ
public:
	BoundingBox();
	~BoundingBox();

	// 幅、高さ、奥行きによって長方体を作り
	HRESULT InitBox(int width, int height, int depth, float alpha);

	// 臨時ーーワールド変換
	void setWorldMatrix(D3DXMATRIX& mtxWorld);

	// バウンディングボックスを描画する
	void Draw();
};


#endif // !_BOUNDING_BOX_CLASS_H_
