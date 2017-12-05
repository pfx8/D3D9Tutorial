//*****************************************************************************
//
// 平面処理[Plane.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Plane.h"

#include "ResourcesManager.h"
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
	m_planeVertexBuff = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Plane::~Plane()
{
	// ポインタ
	RELEASE_POINT(m_planeVertexBuff);
	RELEASE_POINT(m_fieldTexture);
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
void Plane::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;	// 位置
	MakeVertex(size.x, size.y);	// 頂点作成
}

//*****************************************************************************
//
// 座標を設定(多重テクスチャ)
//
//*****************************************************************************
void Plane::InitPlaneDT(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;	// 位置
	MakeVertexDT(size.x, size.y);	// 頂点作成
}

//*****************************************************************************
//
// 頂点作成
//
//*****************************************************************************
HRESULT Plane::MakeVertex(int width, int height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_planeVertexBuff, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 頂点バッファ作成
	VERTEX_3D* VetexBuffer;

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	m_planeVertexBuff->Lock(0, 0, (void**)&VetexBuffer, 0);

	// 頂点バッファの中身を埋める
	// 頂点座標(ローカル座標 = 形を形成してる)
	// もの自身の座標、世界での座標には関係ない
	// m_posFiledは世界での位置で
	
	// position
	VetexBuffer[0].Position = D3DXVECTOR3(-width, 0.0f,  height);
	VetexBuffer[1].Position = D3DXVECTOR3( width, 0.0f,  height);
	VetexBuffer[2].Position = D3DXVECTOR3(-width, 0.0f, -height);
	VetexBuffer[3].Position = D3DXVECTOR3( width, 0.0f, -height);

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

	// 頂点データをアンロックする
	m_planeVertexBuff->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// 頂点作成(多重テクスチャ)
//
//*****************************************************************************
HRESULT Plane::MakeVertexDT(int width, int height)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(NUM_VERTEX * sizeof(VERTEX_3D_DT), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D_DT, D3DPOOL_MANAGED, &m_planeVertexBuff, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 頂点バッファ作成
	VERTEX_3D_DT* VetexBuffer;

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	m_planeVertexBuff->Lock(0, 0, (void**)&VetexBuffer, 0);

	// 頂点バッファの中身を埋める
	// 頂点座標(ローカル座標 = 形を形成してる)
	// もの自身の座標、世界での座標には関係ない
	// m_posFiledは世界での位置で

	// position
	VetexBuffer[0].Position = D3DXVECTOR3(-width, 0.0f, height);
	VetexBuffer[1].Position = D3DXVECTOR3(width, 0.0f, height);
	VetexBuffer[2].Position = D3DXVECTOR3(-width, 0.0f, -height);
	VetexBuffer[3].Position = D3DXVECTOR3(width, 0.0f, -height);

	// tex1
	VetexBuffer[0].TexturePosition0 = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].TexturePosition0 = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].TexturePosition0 = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].TexturePosition0 = D3DXVECTOR2(1.0f, 1.0f);

	// tex2
	VetexBuffer[0].TexturePosition1 = D3DXVECTOR2(0.0f, 0.0f);
	VetexBuffer[1].TexturePosition1 = D3DXVECTOR2(1.0f, 0.0f);
	VetexBuffer[2].TexturePosition1 = D3DXVECTOR2(0.0f, 1.0f);
	VetexBuffer[3].TexturePosition1 = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	m_planeVertexBuff->Unlock();

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
// テクスチャを描画する
//
//*****************************************************************************
void Plane::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetStreamSource(0, m_planeVertexBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_fieldTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//*****************************************************************************
//
// テクスチャを描画する(PixelShader)
//
//*****************************************************************************
void Plane::Draw(LPDIRECT3DTEXTURE9 texture, D3DXCONSTANT_DESC desc1, D3DXCONSTANT_DESC desc2)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, m_planeVertexBuff, 0, sizeof(VERTEX_3D_DT));	// 頂点バッファをデバイスのデータストリームにバイナリ
	pDevice->SetFVF(FVF_VERTEX_3D_DT);	// 頂点フォーマットの設定

	// テクスチャの設定
	pDevice->SetTexture(desc1.RegisterIndex, m_fieldTexture);
	pDevice->SetTexture(desc2.RegisterIndex, texture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//*****************************************************************************
//
// テクスチャを設定
//
//*****************************************************************************
//void Plane::SetTexture(LPDIRECT3DTEXTURE9* point)
//{
//	m_fieldTexture = *point;
//}