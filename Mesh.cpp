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
	SAFE_RELEASE_POINT(m_MeshTexturePoint);

	// クラスポインタ
	SAFE_RELEASE_CLASS_POINT(m_material);
}


//*****************************************************************************
//
// 使いたいメッシュを読み込み
//
//*****************************************************************************
void Mesh::SetMesh(std::string path)
{
	m_path = " ";
	m_path = path;
	ReadXFile();	// パスにより、モデルを読み込み
}

//*****************************************************************************
//
// メッシュを初期かする
//
//*****************************************************************************
HRESULT Mesh::ReadXFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(
		m_path.data(),							// モデルのファイル名
		D3DXMESH_SYSTEMMEM,						// メッシュのメモリ確保オプション
		pDevice,								// デバイスへのポインタ
		NULL,									// 隣接性データを含むバッファへのポインタ
		m_material->GetMaterialPoint(),
		NULL,									// エフェクトインスタンスを含むバッファへのポインタ
		m_material->GetMterialNumber(),
		&m_mesh)))								// メッシュへのポインタ
	{
		return E_FAIL;
	}

	return S_OK;
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
		pDevice->SetTexture(0, m_MeshTexturePoint);

		// 描画
		m_mesh->DrawSubset(count);
	}

	pDevice->SetMaterial(&matDef);	//	マテリアルを元に戻る
}

//*****************************************************************************
//
// メッシュにテクスチャを設定する
//
//*****************************************************************************
void Mesh::SetMeshTexture(PDIRECT3DTEXTURE9* texturePoint)
{
	m_MeshTexturePoint = *texturePoint;
}