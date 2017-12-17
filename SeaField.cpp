//*****************************************************************************
//
// 海面処理 [SeaField.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SeaField.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SeaField::SeaField()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SeaField::~SeaField()
{

}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
HRESULT SeaField::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	m_pos = pos;	// 位置


	{
		m_vertexNum = (planeNum.x + 1) * (planeNum.y + 1);	// 総頂点数
		m_polygonNum = planeNum.x * planeNum.y * 2 + (planeNum.y - 1) * 4;		// ポリゴン数
		m_indexNum = (planeNum.x + 1) * 2 * planeNum.y + (planeNum.y - 1) * 2;	// インデックス数

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// 頂点シェーダー宣言
		{
			D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
			{
				{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
				{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
				{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				D3DDECL_END()
			};
			pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
		}

		// 頂点バッファ作成
		{
			if (FAILED(pDevice->CreateVertexBuffer(m_vertexNum * sizeof(VERTEX_3D_2T), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D_2T, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)))
			{
				std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
				return E_FAIL;
			}

			VERTEX_3D_2T* VertexBuffer;

			// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
			m_vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

			// 頂点バッファの中身を埋める
			// 頂点座標(ローカル座標 = 形を形成してる)
			// もの自身の座標、世界での座標には関係ない
			// m_posFiledは世界での位置で

			for (int numY = 0; numY < (planeNum.y + 1); numY++)
			{
				for (int numX = 0; numX < (planeNum.x + 1); numX++)
				{
					// 頂点座標の設定
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.x = -(planeNum.x / 2.0f) * planeSize.x + numX * planeSize.x;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.y = 0.0f;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.z = (planeNum.y / 2.0f) * planeSize.y - numY * planeSize.y;
					// 法線ベクトルの設定
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
					// テクスチャ1座標の設定
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition1.x = numX * 1.0f;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition1.y = numY * 1.0f;
					// テクスチャ2座標の設定
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition2.x = numX * 0.8f;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition2.y = numY * 0.8f;
				}
			}

			// 頂点データをアンロックする
			m_vertexBuffer->Unlock();
		}

		// 頂点インデックスバッファ作成
		{
			if (FAILED(pDevice->CreateIndexBuffer(m_indexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
			{
				std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
				return E_FAIL;
			}

			WORD* vertexIndex = NULL;		// イデックスの中身を埋める

			m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

			int index = 0;
			for (int numY = 0; numY < planeNum.y; numY++)
			{
				if (numY > 0)
				{// 縮退ポリゴンのためのダブりの設定
					vertexIndex[index] = (numY + 1) * (planeNum.x + 1);
					index++;
				}

				for (int nCntVtxX = 0; nCntVtxX < (planeNum.x + 1); nCntVtxX++)
				{
					vertexIndex[index] = (numY + 1) * (planeNum.x + 1) + nCntVtxX;
					index++;
					vertexIndex[index] = numY * (planeNum.x + 1) + nCntVtxX;
					index++;
				}

				if (numY < (planeNum.y - 1))
				{// 縮退ポリゴンのためのダブりの設定
					vertexIndex[index] = numY * (planeNum.x + 1) + planeNum.x;
					index++;
				}
			}

			m_indexBuffer->Unlock();	// インデックス データのロックを解除する
		}
	}

	return S_OK;
}

//*****************************************************************************
//
// 描画
//
//*****************************************************************************
void SeaField::Draw(Shader* shader)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetVertexDeclaration(m_vertexDecl);								// 頂点宣言を設定
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX_3D_2T));		// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetFVF(FVF_VERTEX_3D_2T);											// 頂点フォーマットの設定
	pDevice->SetIndices(m_indexBuffer);										// 頂点インデックスバッファを設定
	shader->m_effectPoint->SetTexture(shader->m_textureHandle, m_fieldTexture);	// テクスチャの設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_vertexNum, 0, m_polygonNum);	// ポリゴンの描画
}