//*****************************************************************************
//
// 平面処理[Plane.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Plane.h"

#include "../ResourcesManager.h"
//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Plane::Plane()
{
	m_scala = 2;
	m_waveAngle = 0.0f;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
	m_fieldTexture1 = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Plane::~Plane()
{
	// ポインタ
	RELEASE_POINT(m_vertexBuffer);
	RELEASE_POINT(m_fieldTexture1);
	RELEASE_POINT(m_indexBuffer);
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
HRESULT Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	m_pos = pos;	// 位置
	m_planeNum = planeNum;
	m_planeSize = planeSize;

	MakeVertexDecl(m_planeSize, m_planeNum);	// 頂点宣言(shader)

	return S_OK;
}

//*****************************************************************************
//
// 頂点宣言(Shader)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDecl(D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	m_vertexNum = (planeNum.x + 1) * (planeNum.y + 1);	// 総頂点数
	m_polygonNum = planeNum.x * planeNum.y * 2 + (planeNum.y - 1) * 4;		// ポリゴン数
	m_indexNum = (planeNum.x + 1) * 2 * planeNum.y + (planeNum.y - 1) * 2;	// インデックス数

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
			{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
	}

	// 頂点バッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(m_vertexNum * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		VERTEX_3D* VertexBuffer;

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
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.y = 0;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.z = (planeNum.y / 2.0f) * planeSize.y - numY * planeSize.y;
				// 法線ベクトルの設定
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].normalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// 反射光の設定
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
				// テクスチャ1座標の設定
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition.x = numX * 1.0f;
				VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition.y = numY * 1.0f;
			}
		}

		// 頂点データをアンロックする
		m_vertexBuffer->Unlock();
	}

	/*D3DVERTEXBUFFER_DESC pDesc;
	m_vertexBuffer->GetDesc(&pDesc);
	std::cout << "licl" << pDesc.Size << std::endl;*/

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

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Plane::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&m_worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxTranslate);

	// ワールドマトリクスの初期化
	//pDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);
}

//*****************************************************************************
//
// テクスチャを描画する(Shader)
//
//*****************************************************************************
void Plane::Draw(Shader* shader)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	SetWorldMatrix();

	pDevice->SetVertexDeclaration(m_vertexDecl);								// 頂点宣言を設定
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX_3D));			// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetFVF(FVF_VERTEX_3D);											// 頂点フォーマットの設定
	pDevice->SetIndices(m_indexBuffer);										// 頂点インデックスバッファを設定
	shader->m_effectPoint->SetTexture(shader->m_texture1Handle, m_fieldTexture1);	// テクスチャ1の設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_vertexNum, 0, m_polygonNum);	// ポリゴンの描画
}

//*****************************************************************************
//
// 更新
//
//*****************************************************************************
void Plane::Update()
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	m_waveAngle += (rand()%5 + 10) / 5.0f / 180.0f * D3DX_PI;

	if (m_waveAngle > D3DX_PI * 2.0f)
		m_waveAngle = 0.0f;

	VERTEX_3D* VertexBuffer;

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	m_vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

	// 頂点バッファの中身を埋める
	// 頂点座標(ローカル座標 = 形を形成してる)
	// もの自身の座標、世界での座標には関係ない
	// m_posFiledは世界での位置で

	for (int numY = 0; numY < (m_planeNum.y + 1); numY++)
	{
		for (int numX = 0; numX < (m_planeNum.x + 1); numX++)
		{
			VertexBuffer[numY * (int(m_planeNum.x) + 1) + numX].position.y = 0.8 * sinf(numY + numX + m_waveAngle);
		}
	}
}