//*****************************************************************************
//
// 座標変換済み頂点で2D板ポリゴンを描画 [ScreenPolygon.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ScreenPolygon.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ScreenPolygon::ScreenPolygon()
{
	this->vertexDecl = NULL;
	this->indexBuffer = NULL;

	this->UIminiMapVertexBuffer = NULL;
	this->UIminiMapTexture = NULL;

	this->UIKeyVertexBuffer = NULL;
	this->UIKeyTexture = NULL;

	this->HP = 3;
	this->UIHPVertexBuffer[0] = NULL;
	this->UIHPVertexBuffer[1] = NULL;
	this->UIHPVertexBuffer[2] = NULL;
	this->UIHPTexture = NULL;

	// シェーダーを初期化
	this->RHWshader = new RHWShader;
	this->RHWshader->InitShader();

	// リソース管理を初期化
	this->resourcesManager = new ResourcesManager;
	this->resourcesManager->LoadTexture("UIminimap", &this->UIminiMapTexture);
	this->resourcesManager->LoadTexture("UIhp", &this->UIHPTexture);
	this->resourcesManager->LoadTexture("UIkey", &this->UIKeyTexture);

	MakeVertexDecl();
	MakeIndex();

	// 各頂点を作成
	MakeVertex(D3DXVECTOR2(SCREEN_WIDTH - 400, SCREEN_HEIGHT - 400), D3DXVECTOR2(400, 400), &this->UIminiMapVertexBuffer);
	MakeVertex(D3DXVECTOR2(30, 30), D3DXVECTOR2(64, 80), &this->UIHPVertexBuffer[0]);
	MakeVertex(D3DXVECTOR2(114, 30), D3DXVECTOR2(64, 80), &this->UIHPVertexBuffer[1]);
	MakeVertex(D3DXVECTOR2(198, 30), D3DXVECTOR2(64, 80), &this->UIHPVertexBuffer[2]);
	MakeVertex(D3DXVECTOR2(0, SCREEN_HEIGHT - 200), D3DXVECTOR2(200, 200), &this->UIKeyVertexBuffer);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ScreenPolygon::~ScreenPolygon()
{
	RELEASE_POINT(this->vertexDecl);
	RELEASE_POINT(this->indexBuffer);
	
	RELEASE_POINT(this->UIminiMapVertexBuffer);
	RELEASE_POINT(this->UIminiMapTexture);
	RELEASE_POINT(this->UIHPVertexBuffer[0]);
	RELEASE_POINT(this->UIHPVertexBuffer[1]); 
	RELEASE_POINT(this->UIHPVertexBuffer[2]);
	RELEASE_POINT(this->UIHPTexture);
	RELEASE_POINT(this->UIKeyVertexBuffer);
	RELEASE_POINT(this->UIKeyTexture);

	RELEASE_CLASS_POINT(this->resourcesManager);
}

//*****************************************************************************
//
// 頂点宣言
//
//*****************************************************************************
void ScreenPolygon::MakeVertexDecl()
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
}

//*****************************************************************************
//
// 頂点作成
//
//*****************************************************************************
HRESULT ScreenPolygon::MakeVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファ作成
	if (FAILED(pDevice->CreateVertexBuffer(4 * sizeof(VERTEX_2D), D3DUSAGE_WRITEONLY, 0, D3DPOOL_MANAGED, vertexBufferPoint, NULL)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	VERTEX_2D* VertexBuffer;

	// 頂点データの範囲をロックし、頂点バッファ メモリへのポインタを取得する
	(*vertexBufferPoint)->Lock(0, 0, (void**)&VertexBuffer, 0);

	// 頂点座標の設定
	VertexBuffer[0].position = D3DXVECTOR2(pos.x, pos.y);
	VertexBuffer[1].position = D3DXVECTOR2(pos.x + size.x, pos.y);
	VertexBuffer[2].position = D3DXVECTOR2(pos.x, pos.y + size.y);
	VertexBuffer[3].position = D3DXVECTOR2(pos.x + size.x, pos.y + size.y);

	// テクスチャ1座標の設定
	VertexBuffer[0].texturePosition = D3DXVECTOR2(0.0f, 0.0f);
	VertexBuffer[1].texturePosition = D3DXVECTOR2(1.0f, 0.0f);
	VertexBuffer[2].texturePosition = D3DXVECTOR2(0.0f, 1.0f);
	VertexBuffer[3].texturePosition = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データをアンロックする
	(*vertexBufferPoint)->Unlock();

	return S_OK;
}

//*****************************************************************************
//
// インデックス作成
//
//*****************************************************************************
HRESULT ScreenPolygon::MakeIndex()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

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

	return S_OK;
}

//*****************************************************************************
//
// UIを描画する
//
//*****************************************************************************
void ScreenPolygon::Draw()
{
	// minimap
	DrawObject(this->UIminiMapVertexBuffer, this->UIminiMapTexture);

	// HP
	int i = 0;
	while (i < 3)
	{
		DrawObject(this->UIHPVertexBuffer[i], this->UIHPTexture);
		if ((i + 1) == this->HP)
			break;
		else
			i++;
	}
	//DrawObject(this->UIHPVertexBuffer[0], this->UIHPTexture);
	//DrawObject(this->UIHPVertexBuffer[1], this->UIHPTexture);
	//DrawObject(this->UIHPVertexBuffer[2], this->UIHPTexture);

	// 操作ボタン
	DrawObject(this->UIKeyVertexBuffer, this->UIKeyTexture);
}

//*****************************************************************************
//
// 各ものを描画する
//
//*****************************************************************************
void ScreenPolygon::DrawObject(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DTEXTURE9 texture)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクニックを設定
	this->RHWshader->effectPoint->SetTechnique(this->RHWshader->RHWShaderHandle);

	// テクスチャの設定
	this->RHWshader->effectPoint->SetTexture(this->RHWshader->textureHandle, texture);

	// 描画
	UINT passNum = 0;
	this->RHWshader->effectPoint->Begin(&passNum, 0);
	// 各パスを実行する
	for (int count = 0; count < passNum; count++)
	{
		this->RHWshader->effectPoint->BeginPass(0);

		pDevice->SetVertexDeclaration(this->vertexDecl);						// 頂点宣言を設定
		pDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(VERTEX_2D));		// 頂点バッファをデバイスのデータストリームにバイナリ
		pDevice->SetIndices(this->indexBuffer);									// 頂点インデックスバッファを設定
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);		// ポリゴンの描画

		this->RHWshader->effectPoint->EndPass();
	}
	this->RHWshader->effectPoint->End();
}

//*****************************************************************************
//
// 更新する
//
//*****************************************************************************
void ScreenPolygon::Update(Character* player)
{
	this->HP = player->HP;
}