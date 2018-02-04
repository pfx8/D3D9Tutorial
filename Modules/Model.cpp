//*****************************************************************************
//
// モデル処理 [Model.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Model.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Model::Model()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ポインタ
	m_meshPoint = NULL;
	m_meshTexturePoint = NULL;

	// クラスポインタ
	m_material = new Material();

	// 頂点宣言
	D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Model::~Model()
{
	// ポインタ
	RELEASE_POINT(m_meshPoint);
	RELEASE_CLASS_POINT(m_meshTexturePoint);

	// クラスポインタ
	RELEASE_CLASS_POINT(m_material);
}

//*****************************************************************************
//
// モデルを描画する(CelShader)
//
//*****************************************************************************
void Model::DrawModel(CelShader* celShader)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	DWORD materialNum = m_material->m_materialNum;				// マテリアル数を取得

	IDirect3DVertexBuffer9* vertexBuffer = NULL;
	m_meshPoint->GetVertexBuffer(&vertexBuffer);				// メッシュ頂点を取得
	IDirect3DIndexBuffer9* indexBuffer = NULL;
	m_meshPoint->GetIndexBuffer(&indexBuffer);					// メッシュ頂点インデックスバッファを取得

	m_meshPoint->GetAttributeTable(NULL, &materialNum);			// メッシュの属性テーブルに格納されているエントリの数を取得

	D3DXATTRIBUTERANGE* attributes = NULL;						// メッシュの属性テーブルを作る
	attributes = new D3DXATTRIBUTERANGE[materialNum];			// エントリ数によって、属性テーブル配列メモリを作り
	m_meshPoint->GetAttributeTable(attributes, &materialNum);	// メッシュの属性テーブルを取得

	pDevice->SetVertexDeclaration(m_vertexDecl);		// 頂点宣言を設定
	pDevice->SetStreamSource(0, vertexBuffer, 0, 32);	// sizeof(POSITION, NORMAL, UV)
	pDevice->SetIndices(indexBuffer);

	// 描画
	for (DWORD count = 0; count < materialNum; count++)
	{
		if (attributes[count].FaceCount)
		{
			//DWORD matNum = attributes[count].AttribId;			// マテリアル数を取得
			//celShader->m_effectPoint->SetTexture(celShader->m_texture1Handle, m_meshTexturePoint[matNum]);	// テクスチャを設定
			//pDevice->SetTexture(0, m_meshTexturePoint[matNum]);	// テクスチャを設定

			// モデルを描画する
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				attributes[count].VertexStart,
				attributes[count].VertexCount,
				attributes[count].FaceStart * 3,
				attributes[count].FaceCount);
		}
	}

	RELEASE_POINT(vertexBuffer);
	RELEASE_POINT(indexBuffer);

	delete[] attributes;
}