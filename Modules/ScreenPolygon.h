//*****************************************************************************
//
// 座標変換済み頂点で2D板ポリゴンを描画 [ScreenPolygon.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCREEN_POLYGON_H_
#define _SCREEN_POLYGON_H_

#include "..\Engine.h"
#include "..\ResourcesManager.h"
#include "..\Shader\RHWShader.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class ScreenPolygon
{
private:
	RHWShader*					m_RHWshader;		// 変換済み用シェーダー

	void DrawObject(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DTEXTURE9 texture);	// 各ものを描画する
	void MakeVertexDecl();	// 頂点宣言
	HRESULT MakeVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint);	// 頂点作成
	HRESULT MakeIndex();	// インデックス作成
public:
	ResourcesManager*			m_resourcesManager;	// リソースマネジメント
	IDirect3DVertexDeclaration9*m_vertexDecl;		// 頂点シェーダー宣言
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;		// 頂点インデックスバッファ

	LPDIRECT3DVERTEXBUFFER9		m_UIminiMapVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9			m_UIminiMapTexture;			// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9		m_UIHPVertexBuffer;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9			m_UIHPTexture;			// フィールドテクスチャ

	LPDIRECT3DVERTEXBUFFER9		m_UIKeyVertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9			m_UIKeyTexture;			// フィールドテクスチャ

	ScreenPolygon();
	~ScreenPolygon();

	void Draw();
};


#endif // !_SCREEN_POLYGON_H_