//*****************************************************************************
//
// タイトル処理 [SceneTitle.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SceneTitle.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SceneTitle::SceneTitle()
{	
	this->vertexDecl = NULL;
	this->vertexBuffer = NULL;
	this->indexBuffer = NULL;
	this->texture = NULL;

	// シェーダーを初期化
	this->RHWshader = new RHWShader;
	this->RHWshader->InitShader();

	// リソース管理を初期化
	this->resourcesManager = new ResourcesManager;

	// タイトルテクスチャを取得
	this->resourcesManager->LoadTexture("title", &this->texture);

	// 頂点作成
	MakeVertexDecl();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SceneTitle::~SceneTitle()
{
	RELEASE_POINT(this->vertexBuffer);
	RELEASE_POINT(this->vertexDecl);
	RELEASE_POINT(this->indexBuffer);
	RELEASE_POINT(this->texture);

	RELEASE_CLASS_POINT(this->resourcesManager);
}

//*****************************************************************************
//
// 頂点作成
//
//*****************************************************************************
HRESULT SceneTitle::MakeVertexDecl()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
		{
			{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
			{ 0, 8, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD , 0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(planeDecl, &this->vertexDecl);
	}

	// 頂点バッファ作成
	{
		if (FAILED(pDevice->CreateVertexBuffer(4 * sizeof(VERTEX_2D), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, &this->vertexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		VERTEX_2D* VertexBuffer;

		// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
		this->vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

		// 頂点座標の設定
		VertexBuffer[0].position = D3DXVECTOR2(0.0f, 0.0f);
		VertexBuffer[1].position = D3DXVECTOR2(SCREEN_WIDTH, 0.0f);
		VertexBuffer[2].position = D3DXVECTOR2(0.0f, SCREEN_HEIGHT);
		VertexBuffer[3].position = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

		// テクスチャ1座標の設定
		VertexBuffer[0].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
		VertexBuffer[1].texturePosition = D3DXVECTOR2(1.0f, 0.0f);
		VertexBuffer[2].texturePosition = D3DXVECTOR2(0.0f, 1.0f);
		VertexBuffer[3].texturePosition = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		this->vertexBuffer->Unlock();
	}

	// 頂点インデックスバッファ作成
	{
		if (FAILED(pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &this->indexBuffer, NULL)))
		{
			std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
			return E_FAIL;
		}

		WORD* vertexIndex = NULL;		// イデックスの中身を埋める

		this->indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

		vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
		vertexIndex[3] = 2, vertexIndex[4] = 1, vertexIndex[5] = 3;

		this->indexBuffer->Unlock();	// インデックス データのロックを解除する
	}

	return S_OK;
}

//*****************************************************************************
//
// タイトルを描画する
//
//*****************************************************************************
void SceneTitle::Draw()
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクニックを設定
	this->RHWshader->effectPoint->SetTechnique(this->RHWshader->RHWShaderHandle);

	// テクスチャの設定
	this->RHWshader->effectPoint->SetTexture(this->RHWshader->textureHandle, this->texture);

	// 静的な
	int temp = 0;
	this->RHWshader->effectPoint->SetValue("isLL", &temp, sizeof(int));

	// 描画
	UINT passNum = 0;
	this->RHWshader->effectPoint->Begin(&passNum, 0);
	// 各パスを実行する
	for (int count = 0; count < passNum; count++)
	{
		this->RHWshader->effectPoint->BeginPass(0);

		pDevice->SetVertexDeclaration(this->vertexDecl);							// 頂点宣言を設定
		pDevice->SetStreamSource(0, this->vertexBuffer, 0, sizeof(VERTEX_2D));		// 頂点バッファをデバイスのデータストリームにバイナリ
		pDevice->SetIndices(this->indexBuffer);										// 頂点インデックスバッファを設定
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);		// ポリゴンの描画

		this->RHWshader->effectPoint->EndPass();
	}
	this->RHWshader->effectPoint->End();
	
}