//*****************************************************************************
//
// 平面処理[Plane.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _PLANE_H_
#define _PLANE_H_

#include "../Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Plane
{
private:
	int				m_scala;

public:
	float			m_waveAngle;
	D3DXMATRIX		m_worldMatrix;	// ワールド変換マトリックス
	D3DXVECTOR3		m_pos;	// 位置
	//D3DXVECTOR3		m_rot;	// 回転
	//D3DXVECTOR3		m_scl;	// 拡大縮小
	D3DXVECTOR2		m_planeSize;
	D3DXVECTOR2		m_planeNum;
	int				m_vertexNum;		// 頂点数
	int				m_polygonNum;	// ポリゴン数
	int				m_indexNum;		// インデックス数

	IDirect3DVertexDeclaration9*m_vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;	// 頂点インデックスバッファ
	LPDIRECT3DTEXTURE9			m_texture;	// フィールドテクスチャ

	Plane();
	~Plane();

	virtual HRESULT MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// 頂点宣言
	virtual HRESULT InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);	// 座標を設定
	virtual void Draw();				// テクスチャを描画する(PixelShader)
	void SetWorldMatrix();	// 臨時ーーワールド変換
	void Update();
};
#endif // !_PLANE_H_
