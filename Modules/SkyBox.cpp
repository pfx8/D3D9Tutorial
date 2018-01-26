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
	RELEASE_POINT(m_texture);
}

//*****************************************************************************
//
// スカイボックスを初期化
//
//*****************************************************************************
HRESULT SkyBox::InitSkyBox(float length)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	m_length = length;
	
	// 頂点シェーダー宣言
	{
		D3DVERTEXELEMENT9 skyBoxDecl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		device->CreateVertexDeclaration(skyBoxDecl, &m_vertexDecl);
	}

	//頂点バッファを作成
	if (FAILED(device->CreateVertexBuffer(20 * sizeof(SKYBOXVERTEX), 0,
		FVF_SKYBOX, D3DPOOL_MANAGED, &m_vertexBuffer, 0)))
	{
		std::cout << "[Error] 頂点バッファが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 頂点バッファの中身を埋める
	SKYBOXVERTEX vertices[] =
	{
		// 前
		{ { -m_length / 2, 0.0f,			m_length / 2 },{ 0.0f, 1.0f } },
		{ { -m_length / 2, m_length / 2,	m_length / 2 },{ 0.0f, 0.0f } },
		{ { m_length / 2, 0.0f,         m_length / 2 },{ 0.2f, 1.0f } },
		{ { m_length / 2, m_length / 2, m_length / 2 },{ 0.2f, 0.0f } },

		// 後ろ
		{ { m_length / 2, 0.0f,         -m_length / 2 },{ 0.2f, 1.0f } },
		{ { m_length / 2, m_length / 2, -m_length / 2 },{ 0.2f, 0.0f } },
		{ { -m_length / 2, 0.0f,         -m_length / 2 },{ 0.4f, 1.0f } },
		{ { -m_length / 2, m_length / 2, -m_length / 2 },{ 0.4f, 0.0f } },

		// 左
		{ { -m_length / 2, 0.0f,         -m_length / 2 },{ 0.4f, 1.0f } },
		{ { -m_length / 2, m_length / 2, -m_length / 2 },{ 0.4f, 0.0f } },
		{ { -m_length / 2, 0.0f,          m_length / 2 },{ 0.6f, 1.0f } },
		{ { -m_length / 2, m_length / 2,  m_length / 2 },{ 0.6f, 0.0f } },

		// 右
		{ { m_length / 2, 0.0f,          m_length / 2 },{ 0.6f, 1.0f } },
		{ { m_length / 2, m_length / 2,  m_length / 2 },{ 0.6f, 0.0f } },
		{ { m_length / 2, 0.0f,         -m_length / 2 },{ 0.8f, 1.0f } },
		{ { m_length / 2, m_length / 2, -m_length / 2 },{ 0.8f, 0.0f } },

		// 上
		{ { m_length / 2,  m_length / 2, -m_length / 2 },{ 1.0f, 0.0f } },
		{ { m_length / 2,  m_length / 2,  m_length / 2 },{ 1.0f, 1.0f } },
		{ { -m_length / 2, m_length / 2, -m_length / 2 },{ 0.8f, 0.0f } },
		{ { -m_length / 2, m_length / 2,  m_length / 2 },{ 0.8f, 1.0f } },
	};

	void* pVertices;
	m_vertexBuffer->Lock(0, sizeof(vertices), (void**)&pVertices, 0);
	
	// 頂点構造体のデータを頂点バッファにコピー
	memcpy(pVertices, vertices, sizeof(vertices));
	m_vertexBuffer->Unlock();
}


//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void SkyBox::SetWorldMatrix(D3DXMATRIX& mtxWorld)
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
void SkyBox::Draw(Shader *shader)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetVertexDeclaration(m_vertexDecl);							// 頂点宣言を設定
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(SKYBOXVERTEX));	// 頂点バッファをデバイスのデータストリームにバイナリ
	//pDevice->SetFVF(FVF_SKYBOX);											// 頂点フォーマットの設定
	pDevice->SetIndices(m_indexBuffer);										// 頂点イデックスの設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 17, 0, 16);		// バウンディングボックスの描画
}