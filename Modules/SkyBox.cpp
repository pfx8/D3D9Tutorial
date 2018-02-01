//*****************************************************************************
//
// スカイボックス処理 [SkyBox.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SkyBox.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SkyBox::SkyBox()
{
	// 初期化
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_vertexDecl = NULL;
	m_length = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int count = 0; count < 5; count++)
	{
		m_texture[count] = NULL;
	}
	
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SkyBox::~SkyBox()
{
	RELEASE_POINT(m_vertexBuffer);

	for (int count = 0; count < 5; count++)
	{
		RELEASE_POINT(m_texture[count]);
	}
}

//*****************************************************************************
//
// スカイボックスを初期化
//
//*****************************************************************************
HRESULT SkyBox::InitSkyBox(float length)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVERTEXELEMENT9 boundingBoxDecl[] =	// 頂点データのレイアウトを定義
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD },
		D3DDECL_END()
	};
	pDevice->CreateVertexDeclaration(boundingBoxDecl, &m_vertexDecl);

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(20 * sizeof(SKYBOXVERTEX), 0, 0, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 頂点作成
	SKYBOXVERTEX vertex[] =
	{
		// 前
		{ D3DXVECTOR3(-length / 2, 0.0f,       length / 2), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3(-length / 2, length / 2, length / 2), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3( length / 2, 0.0f,       length / 2), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3( length / 2, length / 2, length / 2), D3DXVECTOR2(1.0f, 0.0f) },

		// 後ろ
		{ D3DXVECTOR3( length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 0.0f) },

		// 左
		{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(-length / 2, 0.0f,        length / 2), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },

		// 右
		{ D3DXVECTOR3(length / 2, 0.0f,        length / 2), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3(length / 2, length / 2,  length / 2), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(length / 2, 0.0f,       -length / 2), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3(length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 0.0f) },

		// 上
		{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 1.0f) },
		{ D3DXVECTOR3( length / 2, length / 2,  length / 2), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.0f, 1.0f) },
	};

	VOID* vertexBuffer;	// 頂点バッファポインタ作成

	// 頂点データの範囲をロックして頂点バッファメモリへのポインタを取得する
	if (FAILED(m_vertexBuffer->Lock(0, sizeof(vertex), (void**)&vertexBuffer, 0)))
	{
		std::cout << "[Error] 頂点バッファがロックできない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}
	memcpy(vertexBuffer, vertex, sizeof(vertex));	// 作成された頂点を臨時ポインタの中に入れる
	m_vertexBuffer->Unlock();					// 頂点データをアンロックする

	return S_OK;
}


//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void SkyBox::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&m_mtxWorld);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
}

//*****************************************************************************
//
// スカイボックスを描画
//
//*****************************************************************************
void SkyBox::Draw()
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetVertexDeclaration(m_vertexDecl);							// 頂点宣言を設定
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(SKYBOXVERTEX));	// 頂点バッファをデバイスのデータストリームにバイナリ
	//pDevice->SetIndices(m_indexBuffer);										// 頂点イデックスの設定
	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);		// バウンディングボックスの描画
	for (int count = 0; count < 5; count++)
	{
		pDevice->SetTexture(0, m_texture[count]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, count * 4, 2);
	}
}