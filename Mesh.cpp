//*****************************************************************************
//
// メッシュ処理 [Mesh.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Mesh.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Mesh::Mesh()
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
Mesh::~Mesh()
{
	// ポインタ
	RELEASE_POINT(m_meshPoint);
	RELEASE_CLASS_POINT(m_meshTexturePoint);

	// クラスポインタ
	RELEASE_CLASS_POINT(m_material);
}

//*****************************************************************************
//
// モデルを描画する
//
//*****************************************************************************
void Mesh::DrawModel()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)m_material->m_materialBuffer->GetBufferPointer();

	for (int count = 0; count < (int)(m_material->m_materialNum); count++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[count].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// 描画
		m_meshPoint->DrawSubset(count);
	}

	pDevice->SetMaterial(&matDef);	//	マテリアルを元に戻る
}

//*****************************************************************************
//
// モデルを描画する(Shader)
//
//*****************************************************************************
void Mesh::DrawModel(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	IDirect3DVertexBuffer9* vertexBuffer = NULL;
	m_meshPoint->GetVertexBuffer(&vertexBuffer);	// 頂点バッファを取得

	IDirect3DIndexBuffer9* indexBuffer = NULL;
	m_meshPoint->GetIndexBuffer(&indexBuffer);	// インデックスバッファを取得

	DWORD attributesNum;
	m_meshPoint->GetAttributeTable(NULL, &attributesNum);	// メッシュの属性テーブルに格納されているエントリの数を取得

	D3DXATTRIBUTERANGE* attributes = NULL;
	attributes = new D3DXATTRIBUTERANGE[attributesNum];	// メッシュの属性テーブルを格納できるメモリを作る
	m_meshPoint->GetAttributeTable(attributes, &attributesNum);	// メッシュの属性テーブルを取得


	pDevice->SetVertexShader(vertexShader);	// 頂点シェーダーを設定
	pDevice->SetVertexDeclaration(vertexDecl);	// 頂点シェーダー宣言を設定

	// ストリームを設定
	pDevice->SetStreamSource(0, vertexBuffer, 0, D3DXGetFVFVertexSize(m_meshPoint->GetFVF()));
	pDevice->SetIndices(indexBuffer);

	// 描画
	for (WORD count = 0; count < attributesNum; count++)
	{
		if (attributes[count].FaceCount)
		{
			DWORD matNum = attributes[count].AttribId;	// マテリアル数を取得
			pDevice->SetTexture(0, m_meshTexturePoint[matNum]);	// テクスチャを設定

			// メッシュを描画する
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				attributes[count].VertexStart,
				attributes[count].VertexCount,
				attributes[count].FaceStart * 3, // ?
				attributes[count].FaceCount);
		}
	}

	RELEASE_POINT(vertexBuffer);
	RELEASE_POINT(indexBuffer);
	delete [] attributes;
}