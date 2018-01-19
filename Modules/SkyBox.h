//*****************************************************************************
//
// スカイボックス処理 [SkyBox.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#include "Shader.h"
#include "..\Engine.h"

typedef struct SKYBOXVERTEX
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR2 uv;		// UV座標
}SKYBOXVERTEX;

#define FVF_SKYBOX (D3DFVF_XYZ | D3DFVF_TEX1)


class SkyBox
{
private:
	IDirect3DVertexDeclaration9*	m_vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9			m_vertexBuffer;	// 頂点バッファ
	float							m_length;		// ボックスの長さ

public:
	D3DXMATRIX						m_worldMatrix;	// ワールド変換マトリックス
	LPDIRECT3DTEXTURE9				m_texture[5];	// テクスチャ配列
	// [0]前 [1]後ろ [2]左 [3]右 [4]上
	
	SkyBox();
	~SkyBox();

	HRESULT InitSkyBox(float length);	// スカイボックスを初期化
	void Draw(Shader *shader);	// スカイボックスを描画
};