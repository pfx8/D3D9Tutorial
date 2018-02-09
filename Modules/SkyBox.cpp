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

	m_texture = NULL;
	m_length = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SkyBox::~SkyBox()
{
	RELEASE_POINT(m_vertexBuffer);
	RELEASE_POINT(m_indexBuffer);
	RELEASE_POINT(m_vertexDecl);
	RELEASE_POINT(m_texture);
}

//*****************************************************************************
//
// スカイボックスを初期化
//
//*****************************************************************************
HRESULT SkyBox::InitSkyBox(float length)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	{// 頂点設計
		D3DVERTEXELEMENT9 boundingBoxDecl[] =	// 頂点データのレイアウトを定義
		{
			{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION },
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(boundingBoxDecl, &m_vertexDecl);

		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(4 * sizeof(SKYBOXVERTEX), D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &m_vertexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		// 頂点作成
		SKYBOXVERTEX vertex[] =
		{
			// 前
			{ D3DXVECTOR3(-length / 2, length / 2, length / 2), D3DXVECTOR2(0.0f, 0.0f) },
			{ D3DXVECTOR3( length / 2, length / 2, length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			{ D3DXVECTOR3(-length / 2, 0.0f,       length / 2), D3DXVECTOR2(0.0f, 1.0f) },
			{ D3DXVECTOR3( length / 2, 0.0f,       length / 2), D3DXVECTOR2(1.0f, 1.0f) },

			//// 後ろ
			//{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.0f, 0.0f) },
			//{ D3DXVECTOR3( length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.0f, 1.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			//{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(1.0f, 1.0f) },

			//// 左
			//{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(0.0f, 0.0f) },
			//{ D3DXVECTOR3(-length / 2, 0.0f,       -length / 2), D3DXVECTOR2(0.0f, 1.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			//{ D3DXVECTOR3(-length / 2, 0.0f,        length / 2), D3DXVECTOR2(1.0f, 1.0f) },

			//// 右
			//{ D3DXVECTOR3(length / 2, length / 2,  length / 2), D3DXVECTOR2(0.0f, 0.0f) },
			//{ D3DXVECTOR3(length / 2, 0.0f,        length / 2), D3DXVECTOR2(0.0f, 1.0f) },
			//{ D3DXVECTOR3(length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			//{ D3DXVECTOR3(length / 2, 0.0f,       -length / 2), D3DXVECTOR2(1.0f, 1.0f) },

			//// 上
			//{ D3DXVECTOR3( length / 2, length / 2,  length / 2), D3DXVECTOR2(0.0f, 0.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2,  length / 2), D3DXVECTOR2(1.0f, 0.0f) },
			//{ D3DXVECTOR3( length / 2, length / 2, -length / 2), D3DXVECTOR2(0.0f, 1.0f) },
			//{ D3DXVECTOR3(-length / 2, length / 2, -length / 2), D3DXVECTOR2(1.0f, 1.0f) },
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
	}

	{// インデックス設計
		//オブジェクトの頂点インデックスバッファを生成
		if (FAILED(pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		WORD* vertexIndex = NULL;	// イデックスの中身を埋める
		m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

		// 前
		vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
		vertexIndex[3] = 1, vertexIndex[4] = 2, vertexIndex[5] = 3;

		//// 後ろ
		//vertexIndex[6] = 4, vertexIndex[7] = 5, vertexIndex[8] = 6;
		//vertexIndex[9] = 5, vertexIndex[10] = 6, vertexIndex[11] = 7;

		//// 左
		//vertexIndex[12] = 8, vertexIndex[13] = 9, vertexIndex[14] = 10;
		//vertexIndex[15] = 9, vertexIndex[16] = 10, vertexIndex[17] = 11;

		//// 右
		//vertexIndex[18] = 12, vertexIndex[19] = 13, vertexIndex[20] = 14;
		//vertexIndex[21] = 13, vertexIndex[22] = 14, vertexIndex[23] = 15;

		//// 上
		//vertexIndex[24] = 16, vertexIndex[25] = 17, vertexIndex[26] = 18;
		//vertexIndex[27] = 17, vertexIndex[28] = 18, vertexIndex[29] = 19;

		// インデックス データのロックを解除する
		m_indexBuffer->Unlock();
	}

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

	pDevice->SetVertexDeclaration(m_vertexDecl);							// 頂点宣言を設定
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(SKYBOXVERTEX));	// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetIndices(m_indexBuffer);										// 頂点イデックスの設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);		// バウンディングボックスの描画
}