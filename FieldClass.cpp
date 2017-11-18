//*****************************************************************************
//
// フィールド処理[FieldClass.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "FieldClass.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Field::Field()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ポインタ
	m_VertexBuffField = NULL;

	// クラスポインタ
	m_textureManager = new TextureManager();

	// 頂点作成
	MakeVertex();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Field::~Field()
{
	// ポインタ
	SAFE_RELEASE_POINT(m_VertexBuffField);

	// クラスポインタ
	SAFE_RELEASE_CLASS_POINT(m_textureManager);
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
void Field::InitCoordinate(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//*****************************************************************************
//
// 頂点作成
//
//*****************************************************************************
HRESULT Field::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VertexBuffField, NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファ作成
	VERTEX_3D* VetexBuffer;

	m_VertexBuffField->Lock(0, 0, (void**)&VetexBuffer, 0);

	// 頂点バッファの中身を埋める
	// 頂点座標(ローカル座標 = 形を形成してる)
	// もの自身の座標、世界での座標には関係ない
	// m_posFiledは世界での位置で
	
	// position
	VetexBuffer[0].Position = m_pos + D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	VetexBuffer[1].Position = m_pos + D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	VetexBuffer[2].Position = m_pos + D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	VetexBuffer[3].Position = m_pos + D3DXVECTOR3(100.0f, 0.0f, -100.0f);

	// normal
	VetexBuffer[0].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	VetexBuffer[1].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	VetexBuffer[2].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	VetexBuffer[3].NormalVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// diffuse
	VetexBuffer[0].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	VetexBuffer[1].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	VetexBuffer[2].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);
	VetexBuffer[3].diffuse = D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f);

	// tex
	VetexBuffer[0].TexturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].TexturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].TexturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].TexturePosition = D3DXVECTOR2(1.0f, 1.0f);

	m_VertexBuffField->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Field::setWorldMatrix(D3DXMATRIX& mtxWorld)
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
void Field::DrawField()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// レンダリングデフォルトモード
	// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetStreamSource(0, m_VertexBuffField, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	Texture* p = m_textureManager->GetTexture(0);
	pDevice->SetTexture(0, p->TexturePoint);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}