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

	m_meshPoint->GetAttributeTable(NULL, &materialNum);		// メッシュの属性テーブルに格納されているエントリの数を取得

	D3DXATTRIBUTERANGE* attributes = NULL;						// メッシュの属性テーブルを作る
	attributes = new D3DXATTRIBUTERANGE[materialNum];			// エントリ数によって、属性テーブル配列メモリを作り
	m_meshPoint->GetAttributeTable(attributes, &materialNum);	// メッシュの属性テーブルを取得

	// ストリームを設定
	pDevice->SetStreamSource(0, vertexBuffer, 0, D3DXGetFVFVertexSize(m_meshPoint->GetFVF()));
	pDevice->SetIndices(indexBuffer);

	// 描画
	for (DWORD count = 0; count < materialNum; count++)
	{
		if (attributes[count].FaceCount)
		{
			//DWORD matNum = attributes[count].AttribId;			// マテリアル数を取得
			//celShader->m_effectPoint->SetTexture(celShader->m_texture1Handle, m_meshTexturePoint[matNum]);	// テクスチャを設定
			//pDevice->SetTexture(0, m_meshTexturePoint[matNum]);	// テクスチャを設定

			// マテリアルを渡す
			celShader->m_effectPoint->SetValue("materialAmbientColor", &m_material->m_materialPoint[count].Ambient, sizeof(D3DXVECTOR3));
			celShader->m_effectPoint->SetValue("materialDiffuseColor", &m_material->m_materialPoint[count].Diffuse, sizeof(D3DXCOLOR));
			

			UINT passNum = 0;	// パスの数
			celShader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				celShader->m_effectPoint->BeginPass(count);

				pDevice->DrawIndexedPrimitive(				// メッシュを描画する
					D3DPT_TRIANGLELIST,
					0,
					attributes[count].VertexStart,
					attributes[count].VertexCount,
					attributes[count].FaceStart * 3,
					attributes[count].FaceCount);

				celShader->m_effectPoint->EndPass();
			}
			celShader->m_effectPoint->End();
			
		}
	}

	RELEASE_POINT(vertexBuffer);
	RELEASE_POINT(indexBuffer);

	delete[] attributes;
}