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
	m_mesh = NULL;
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
	SAFE_RELEASE_POINT(m_mesh);
	SAFE_RELEASE_POINT(m_meshTexturePoint);

	// クラスポインタ
	SAFE_RELEASE_CLASS_POINT(m_material);
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
	pD3DXMat = (D3DXMATERIAL*)(*m_material->GetMaterialPoint())->GetBufferPointer();

	for (int count = 0; count < (int)*(m_material->GetMterialNumber()); count++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[count].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_meshTexturePoint);

		// 描画
		m_mesh->DrawSubset(count);
	}

	pDevice->SetMaterial(&matDef);	//	マテリアルを元に戻る
}