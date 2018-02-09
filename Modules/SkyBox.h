//*****************************************************************************
//
// スカイボックス処理 [SkyBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SKY_BOX_H_
#define _SKY_BOX_H_

#include "Shader.h"
#include "..\Engine.h"

typedef struct SKYBOXVERTEX
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR2 uv;		// UV座標
}SKYBOXVERTEX;

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SkyBox
{
private:
	D3DXVECTOR3						m_pos;			// 座標
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9			m_vertexBuffer;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9			m_indexBuffer;	// インデックスバッファ
	D3DXMATRIX						m_mtxWorld;		// ワールド変換行列
	float							m_length;		// ボックスの長さ

public:
	D3DXMATRIX						m_worldMatrix;	// ワールド変換マトリックス
	LPDIRECT3DTEXTURE9				m_texture;		// テクスチャ配列
	
	SkyBox();
	~SkyBox();

	HRESULT InitSkyBox(float length);		// スカイボックスを初期化
	void SetWorldMatrix();					// 臨時ーーワールド変換
	void Draw();							// スカイボックスを描画
};

#endif // !_SKY_BOX_H_