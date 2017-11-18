//*****************************************************************************
//
// メッシュクラス [MeshClass.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "MeshClass.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Mesh::Mesh()
{
	// ポインタ
	m_mesh = NULL;
	m_path = " ";

	// クラスポインタ
	m_material = new Material();
	m_textureManager = new TextureManager();
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

	// クラスポインタ
	SAFE_RELEASE_CLASS_POINT(m_material);
	SAFE_RELEASE_CLASS_POINT(m_textureManager);
}


//*****************************************************************************
//
// 使いたいメッシュを読み込み
//
//*****************************************************************************
void Mesh::SetMesh(std::string path)
{
	m_path = path;
	ReadXFile();
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
		Texture *p = m_textureManager->GetTexture(3);
		pDevice->SetTexture(0, p->TexturePoint);

		// 描画
		m_mesh->DrawSubset(count);
	}

	pDevice->SetMaterial(&matDef);	//	マテリアルを元に戻る
}

