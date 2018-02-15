
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
	this->pos  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl  = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	this->size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	this->indexBuffer = NULL;
	this->vertexBuffer = NULL;
	this->vertexDecl = NULL;

	this->isBoundingBoxDraw = false;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
BoundingBox::~BoundingBox()
{
	// ポインタ
	RELEASE_POINT(this->indexBuffer);
	RELEASE_POINT(this->vertexBuffer);
	RELEASE_POINT(this->vertexDecl);
}

//*****************************************************************************
//
// 幅、高さ、奥行きによって長方体を作り
//
//*****************************************************************************
void BoundingBox::InitBox(int width, int height, int depth, float alpha)
{
	this->size = D3DXVECTOR3((float)width, (float)height, (float)depth);
	this->alpha = alpha;

	MakeVertex();
}

//*****************************************************************************
//
// 長方体頂点を設定
//
//*****************************************************************************
HRESULT BoundingBox::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	{// 頂点設計
		D3DVERTEXELEMENT9 boundingBoxDecl[] =	// 頂点データのレイアウトを定義
		{
			{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION },
			{ 0, 12, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR    },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(boundingBoxDecl, &this->vertexDecl);

		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(8 * sizeof(BOUNDINGBOXVERTEX), 0, 0, D3DPOOL_DEFAULT, &this->vertexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		// 頂点作成
		BOUNDINGBOXVERTEX vertex[] =
		{
			// 座標、diffuse
			{ D3DXVECTOR3(-this->size.x / 2,  this->size.y / 2, -this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) },
			{ D3DXVECTOR3(-this->size.x / 2,  this->size.y / 2,  this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) },
			{ D3DXVECTOR3( this->size.x / 2,  this->size.y / 2,  this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) },
			{ D3DXVECTOR3( this->size.x / 2,  this->size.y / 2, -this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) },
			{ D3DXVECTOR3(-this->size.x / 2,                 0, -this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) },
			{ D3DXVECTOR3(-this->size.x / 2,                 0,  this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) },
			{ D3DXVECTOR3( this->size.x / 2,                 0,  this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) },
			{ D3DXVECTOR3( this->size.x / 2,                 0, -this->size.z / 2), D3DXCOLOR(1.0f, 0.0f, 0.0f, this->alpha) }
		};

		VOID* vertexBuffer;	// 頂点バッファポインタ作成

		// 頂点データの範囲をロックして頂点バッファメモリへのポインタを取得する
		if (FAILED(this->vertexBuffer->Lock(0, sizeof(vertex), (void**)&vertexBuffer, 0)))
		{
			std::cout << "[Error] 頂点バッファがロックできない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}
		memcpy(vertexBuffer, vertex, sizeof(vertex));	// 作成された頂点を臨時ポインタの中に入れる
		this->vertexBuffer->Unlock();					// 頂点データをアンロックする
	}


	{
		// インデックス設計
		// オブジェクトの頂点インデックスバッファを生成
		if (FAILED(pDevice->CreateIndexBuffer(36 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		WORD* vertexIndex = NULL;	// イデックスの中身を埋める
		this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

		// 底面(上)
		vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
		vertexIndex[3] = 0, vertexIndex[4] = 2, vertexIndex[5] = 3;

		// 正面
		vertexIndex[6] = 0, vertexIndex[7] = 3, vertexIndex[8] = 7;
		vertexIndex[9] = 0, vertexIndex[10] = 7, vertexIndex[11] = 4;

		// 侧面(左)
		vertexIndex[12] = 0, vertexIndex[13] = 4, vertexIndex[14] = 5;
		vertexIndex[15] = 0, vertexIndex[16] = 5, vertexIndex[17] = 1;

		// 侧面(右)
		vertexIndex[18] = 2, vertexIndex[19] = 6, vertexIndex[20] = 7;
		vertexIndex[21] = 2, vertexIndex[22] = 7, vertexIndex[23] = 3;

		// 背面
		vertexIndex[24] = 2, vertexIndex[25] = 5, vertexIndex[26] = 6;
		vertexIndex[27] = 2, vertexIndex[28] = 1, vertexIndex[29] = 5;

		// 底面(下)
		vertexIndex[30] = 4, vertexIndex[31] = 6, vertexIndex[32] = 5;
		vertexIndex[33] = 4, vertexIndex[34] = 7, vertexIndex[35] = 6;

		// インデックス データのロックを解除する
		this->indexBuffer->Unlock();
	}

	return S_OK;
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void BoundingBox::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&this->worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, this->scl.x, this->scl.y, this->scl.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->rot.y, this->rot.x, this->rot.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// テクスチャを描画する
//
//*****************************************************************************
void BoundingBox::Draw(Shader* shader, D3DXMATRIX* VPMatrix)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	SetWorldMatrix();

	// テクニックを設定
	shader->shaderHandle = shader->effectPoint->GetTechniqueByName("RenderWithoutTextrue");
	shader->effectPoint->SetTechnique(shader->shaderHandle);

	// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
	shader->effectPoint->SetMatrix(shader->WMatrixHandle, &this->worldMatrix);
	shader->effectPoint->SetMatrix(shader->VPMatrixHandle, VPMatrix);

	// アルファ値の設定(テクスチャ無し)
	shader->effectPoint->SetFloat(shader->alphaHandle, 0.2f);

	UINT passNum = 0;
	shader->effectPoint->Begin(&passNum, 0);
	for (int count = 0; count < passNum; count++)
	{
		shader->effectPoint->BeginPass(0);

		pDevice->SetVertexDeclaration(this->vertexDecl);								// 頂点シェーダー設定
		pDevice->SetStreamSource(0, this->vertexBuffer, 0, sizeof(BOUNDINGBOXVERTEX));	// 頂点バッファをデバイスのデータストリームにバイナリ
		pDevice->SetIndices(this->indexBuffer);											// 頂点イデックスの設定
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);				// バウンディングボックスの描画

		shader->effectPoint->EndPass();
	}
	shader->effectPoint->End();
	
}