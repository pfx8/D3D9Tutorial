//*****************************************************************************
//
// バウンディングボックス処理[BoundingBox.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "BoundingBox.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
BoundingBox::BoundingBox()
{
	m_pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl  = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_indexBuffer = NULL;
	m_vertexBuffer = NULL;

	m_isBoundingBoxDraw = true;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
BoundingBox::~BoundingBox()
{
	// ポインタ
	RELEASE_POINT(m_indexBuffer);
	RELEASE_POINT(m_vertexBuffer);
}

//*****************************************************************************
//
// 長方体頂点を設定
//
//*****************************************************************************
HRESULT BoundingBox::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Vertex

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(8 * sizeof(VERTEX_3D_NT), 0, FVF_VERTEX_3D_NT, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 頂点作成
	VERTEX_3D_NT Vetex[] =
	{
		// 座標、法線、diffuse
		{ D3DXVECTOR3(-m_size.x / 2,  m_size.y / 2, -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3(-m_size.x / 2,  m_size.y / 2,  m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  m_size.y / 2,  m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  m_size.y / 2, -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3(-m_size.x / 2,  0,           -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3(-m_size.x / 2,  0,            m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  0,            m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) },
		{ D3DXVECTOR3( m_size.x / 2,  0,           -m_size.z / 2), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXCOLOR(255.0f, 0.0f, 0.0f, m_alpha) }
	};

	// 頂点バッファポインタ作成
	VOID* VertexBuffer;

	// 頂点データの範囲をロックして頂点バッファメモリへのポインタを取得する
	if (FAILED(m_vertexBuffer->Lock(0, sizeof(Vetex), (void**)&VertexBuffer, 0)))
	{
		std::cout << "[Error] 頂点バッファがロックできない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 作成された頂点を臨時ポインタの中に入れる
	memcpy(VertexBuffer, Vetex, sizeof(Vetex));

	// 頂点データをアンロックする
	m_vertexBuffer->Unlock();

	// Index

	//オブジェクトの頂点インデックスバッファを生成
	if (FAILED(pDevice->CreateIndexBuffer(36 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// イデックスの中身を埋める
	WORD* VertexIndex = NULL;

	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する
	m_indexBuffer->Lock(0, 0, (void**)&VertexIndex, 0);

	// 底面(上)
	VertexIndex[0] = 0, VertexIndex[1] = 1, VertexIndex[2] = 2;
	VertexIndex[3] = 0, VertexIndex[4] = 2, VertexIndex[5] = 3;

	// 正面
	VertexIndex[6] = 0, VertexIndex[7] = 3, VertexIndex[8] = 7;
	VertexIndex[9] = 0, VertexIndex[10] = 7, VertexIndex[11] = 4;

	// 侧面(左)
	VertexIndex[12] = 0, VertexIndex[13] = 4, VertexIndex[14] = 5;
	VertexIndex[15] = 0, VertexIndex[16] = 5, VertexIndex[17] = 1;

	// 侧面(右)
	VertexIndex[18] = 2, VertexIndex[19] = 6, VertexIndex[20] = 7;
	VertexIndex[21] = 2, VertexIndex[22] = 7, VertexIndex[23] = 3;

	// 背面
	VertexIndex[24] = 2, VertexIndex[25] = 5, VertexIndex[26] = 6;
	VertexIndex[27] = 2, VertexIndex[28] = 1, VertexIndex[29] = 5;

	// 底面(下)
	VertexIndex[30] = 4, VertexIndex[31] = 6, VertexIndex[32] = 5;
	VertexIndex[33] = 4, VertexIndex[34] = 7, VertexIndex[35] = 6;

	// インデックス データのロックを解除する
	m_indexBuffer->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// 幅、高さ、奥行きによって長方体を作り
//
//*****************************************************************************
void BoundingBox::InitBox(int width, int height, int depth, float alpha)
{
	m_size = D3DXVECTOR3((float)width, (float)height, (float)depth);
	m_alpha = alpha;

	MakeVertex();
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void BoundingBox::SetWorldMatrix(D3DXMATRIX& mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリクスの初期化
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
}

//*****************************************************************************
//
// テクスチャを描画する
//
//*****************************************************************************
void BoundingBox::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX_3D_NT));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D_NT);

	// 頂点イデックスの設定
	pDevice->SetIndices(m_indexBuffer);

	// バウンディングボックスの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);
}

//*****************************************************************************
//
// 当たり判定(長方体)
//
//*****************************************************************************
//bool BoundingBox::CheckHitBB(Character* Object)
//{
//
//}