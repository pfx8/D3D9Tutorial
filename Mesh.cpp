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
//void Mesh::DrawModel()
//{
//	LPDIRECT3DDEVICE9 pDevice = GetDevice();
//
//	D3DXMATERIAL *pD3DXMat;
//	D3DMATERIAL9 matDef;
//
//	// 現在のマテリアルを取得
//	pDevice->GetMaterial(&matDef);
//
//	// マテリアル情報に対するポインタを取得
//	pD3DXMat = (D3DXMATERIAL*)m_material->m_materialPoint->GetBufferPointer();
//
//	for (int count = 0; count < (int)(m_material->m_materialNum); count++)
//	{
//		// マテリアルの設定
//		pDevice->SetMaterial(&pD3DXMat[count].MatD3D);
//
//		// テクスチャの設定
//		pDevice->SetTexture(0, NULL);
//
//		// 描画
//		m_meshPoint->DrawSubset(count);
//	}
//
//	pDevice->SetMaterial(&matDef);	//	マテリアルを元に戻る
//}

//*****************************************************************************
//
// モデルを描画する(Shader)
//
//*****************************************************************************
void Mesh::DrawModel(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	IDirect3DVertexBuffer9* vertexBuffer = NULL;	// 頂点バッファ
	IDirect3DIndexBuffer9* indexBuffer = NULL;	// インデックスバッファ

	m_meshPoint->GetVertexBuffer(&vertexBuffer);
	m_meshPoint->GetIndexBuffer(&indexBuffer);

	// 
	DWORD numAttributes;
	D3DXATTRIBUTERANGE* attributes = NULL;
	m_meshPoint->GetAttributeTable(NULL, &numAttributes);
	attributes = new D3DXATTRIBUTERANGE[numAttributes];
	m_meshPoint->GetAttributeTable(attributes, &numAttributes);

	// 頂点シェーダーと頂点シェーダ宣言を設定
	pDevice->SetVertexShader(vertexShader);
	pDevice->SetVertexDeclaration(vertexDecl);

	// ストリームを設定
	pDevice->SetStreamSource(0, vertexBuffer, 0, D3DXGetFVFVertexSize(m_meshPoint->GetFVF()));
	pDevice->SetIndices(indexBuffer);

	// ドロー
	for (WORD count = 0; count < numAttributes; count++)
	{
		if (attributes[count].FaceCount)
		{
			// マテリアル数を取得
			DWORD matNum = attributes[count].AttribId;

			// テクスチャを設定
			pDevice->SetTexture(0, m_meshTexturePoint[matNum]);

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