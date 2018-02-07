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
	m_vertexDecl = NULL;
	m_indexBuffer = NULL;

	m_UIminiMapVertexBuffer = NULL;
	m_UIminiMapTexture = NULL;

	m_UIHPVertexBuffer = NULL;
	m_UIHPTexture = NULL;

	m_UIKeyVertexBuffer = NULL;
	m_UIKeyTexture = NULL;

	// シェーダーを初期化
	m_RHWshader = new RHWShader;
	m_RHWshader->InitShader();

	// リソース管理を初期化
	m_resourcesManager = new ResourcesManager;
	m_resourcesManager->LoadTexture("UIminimap", &m_UIminiMapTexture);
	m_resourcesManager->LoadTexture("UIHP", &m_UIHPTexture);
	m_resourcesManager->LoadTexture("UIkey", &m_UIKeyTexture);

	MakeVertexDecl();
	MakeIndex();

	// 各頂点を作成
	MakeVertex(D3DXVECTOR2(SCREEN_WIDTH - 200, SCREEN_HEIGHT - 200), D3DXVECTOR2(200, 200), &m_UIminiMapVertexBuffer);
	MakeVertex(D3DXVECTOR2(0, 30), D3DXVECTOR2(400, 50), &m_UIHPVertexBuffer);
	MakeVertex(D3DXVECTOR2(0, SCREEN_HEIGHT - 200), D3DXVECTOR2(200, 200), &m_UIKeyVertexBuffer);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ScreenPolygon::~ScreenPolygon()
{
	RELEASE_POINT(m_vertexDecl);
	RELEASE_POINT(m_indexBuffer);
	
	RELEASE_POINT(m_UIminiMapVertexBuffer);
	RELEASE_POINT(m_UIminiMapTexture);
	RELEASE_POINT(m_UIHPVertexBuffer);
	RELEASE_POINT(m_UIHPTexture);
	RELEASE_POINT(m_UIKeyVertexBuffer);
	RELEASE_POINT(m_UIKeyTexture);

	RELEASE_CLASS_POINT(m_resourcesManager);
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
		pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
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

	if (FAILED(pDevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
	{
		std::cout << "[Error] 頂点インデクスが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	WORD* vertexIndex = NULL;		// イデックスの中身を埋める

	m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// インデックス データのある一定範囲をロックし、そのインデックス バッファー メモリーへのポインターを取得する

	vertexIndex[0] = 0, vertexIndex[1] = 1, vertexIndex[2] = 2;
	vertexIndex[3] = 2, vertexIndex[4] = 1, vertexIndex[5] = 3;

	m_indexBuffer->Unlock();	// インデックス データのロックを解除する

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
	DrawObject(m_UIminiMapVertexBuffer, m_UIminiMapTexture);

	// HP
	DrawObject(m_UIHPVertexBuffer, m_UIHPTexture);

	// 操作ボタン
	DrawObject(m_UIKeyVertexBuffer, m_UIKeyTexture);
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
	m_RHWshader->m_effectPoint->SetTechnique(m_RHWshader->m_RHWShaderHandle);

	// テクスチャの設定
	m_RHWshader->m_effectPoint->SetTexture(m_RHWshader->m_textureHandle, texture);

	// 描画
	UINT passNum = 0;
	m_RHWshader->m_effectPoint->Begin(&passNum, 0);
	// 各パスを実行する
	for (int count = 0; count < passNum; count++)
	{
		m_RHWshader->m_effectPoint->BeginPass(0);

		pDevice->SetVertexDeclaration(m_vertexDecl);							// 頂点宣言を設定
		pDevice->SetStreamSource(0, vertexBuffer, 0, sizeof(VERTEX_2D));		// 頂点バッファをデバイスのデータストリームにバイナリ
		pDevice->SetIndices(m_indexBuffer);										// 頂点インデックスバッファを設定
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);		// ポリゴンの描画

		m_RHWshader->m_effectPoint->EndPass();
	}
	m_RHWshader->m_effectPoint->End();
}