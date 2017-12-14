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
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	m_vertexBuffer = NULL;
	m_indexBuffer = NULL;
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
	RELEASE_POINT(m_fieldTexture);
	RELEASE_POINT(m_indexBuffer);
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
void Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;	// 位置
	MakeVertexDecl(size.x, size.y);	// 頂点宣言(shader)
}

//*****************************************************************************
//
// 頂点宣言(Shader)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDecl(int width, int height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
		{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);	// 頂点データを作る

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 頂点バッファ作成
	VERTEX_3D* VetexBuffer;

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	m_vertexBuffer->Lock(0, 0, (void**)&VetexBuffer, 0);

	// 頂点バッファの中身を埋める
	// 頂点座標(ローカル座標 = 形を形成してる)
	// もの自身の座標、世界での座標には関係ない
	// m_posFiledは世界での位置で

	// 頂点座標の設定
	VetexBuffer[0].position = D3DXVECTOR3(-width, 0.0f, height);
	VetexBuffer[1].position = D3DXVECTOR3(width, 0.0f, height);
	VetexBuffer[2].position = D3DXVECTOR3(-width, 0.0f, -height);
	VetexBuffer[3].position = D3DXVECTOR3(width, 0.0f, -height);

	// 法線ベクトルの設定
	VetexBuffer[0].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VetexBuffer[1].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VetexBuffer[2].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	VetexBuffer[3].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	// 反射光の設定
	VetexBuffer[0].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VetexBuffer[1].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VetexBuffer[2].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	VetexBuffer[3].diffuse = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	VetexBuffer[0].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].texturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].texturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].texturePosition = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	m_vertexBuffer->Unlock();


	//オブジェクトの頂点インデックスバッファを生成
	if (FAILED(pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}
	WORD* vertexIndex = NULL;							// イデックスの中身を埋める
	m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

	vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 3;
	vertexIndex[3] = 0, vertexIndex[4] = 3, vertexIndex[5] = 2;

	m_indexBuffer->Unlock();	// インデックス データのロックを解除する

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Plane::SetWorldMatrix(D3DXMATRIX& mtxWorld)
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
// テクスチャを描画する(Shader)
//
//*****************************************************************************
void Plane::Draw(Shader* shader)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetVertexDeclaration(m_vertexDecl);								// 頂点宣言を設定
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX_3D));			// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetFVF(FVF_VERTEX_3D);												// 頂点フォーマットの設定
	pDevice->SetIndices(m_indexBuffer);											// 頂点インデックスバッファを設定
	shader->m_effectPoint->SetTexture(shader->m_textureHandle, m_fieldTexture);	// テクスチャの設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, NUM_POLYGON);	// ポリゴンの描画
}