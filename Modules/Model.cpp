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
	// ポインタ
	m_meshPoint = NULL;
	m_meshTexturePoint = NULL;

	// クラスポインタ
	m_material = new Material();
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
// モデルを描画する(Effect)
//
//*****************************************************************************
void Model::DrawModel(Shader* shader)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	IDirect3DVertexBuffer9* vertexBuffer = NULL;				// 頂点バッファを取得
	m_meshPoint->GetVertexBuffer(&vertexBuffer);
	IDirect3DIndexBuffer9* indexBuffer = NULL;					// インデックスバッファを取得
	m_meshPoint->GetIndexBuffer(&indexBuffer);

	DWORD attributesNum;										// メッシュの属性テーブルに格納されているエントリの数を取得
	m_meshPoint->GetAttributeTable(NULL, &attributesNum);
	D3DXATTRIBUTERANGE* attributes = NULL;						// メッシュの属性テーブルを作る
	attributes = new D3DXATTRIBUTERANGE[attributesNum];		// エントリ数によって、属性テーブル配列メモリを作り
	m_meshPoint->GetAttributeTable(attributes, &attributesNum);	// メッシュの属性テーブルを取得

	// ストリームを設定
	pDevice->SetStreamSource(0, vertexBuffer, 0, D3DXGetFVFVertexSize(m_meshPoint->GetFVF()));
	pDevice->SetIndices(indexBuffer);

	// 描画
	for (WORD count = 0; count < attributesNum; count++)
	{
		if (attributes[count].FaceCount)
		{
			DWORD matNum = attributes[count].AttribId;			// マテリアル数を取得
			//shader->m_effectPoint->SetTexture(shader->m_texture1Handle, m_meshTexturePoint[matNum]);	// テクスチャを設定
			pDevice->SetTexture(0, m_meshTexturePoint[matNum]);	// テクスチャを設定
			pDevice->DrawIndexedPrimitive(					// メッシュを描画する
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