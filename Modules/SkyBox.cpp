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
	for (int count = 0; count < 5; count++)
	{
		m_texture[count] = NULL;
	}
	m_length = 0.0f;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SkyBox::~SkyBox()
{
	RELEASE_POINT(m_vertexBuffer);
	for (int count = 0; count < 5; count++)
	{
		RELEASE_POINT(m_texture[count]);
	}
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
		D3DVERTEXELEMENT9 planeDecl[] =		// 頂点データのレイアウトを定義
		{
			{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
			{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
			{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
		};
		device->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
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
		{ {-m_length / 2, 0.0f,			m_length / 2}, {0.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2,	m_length / 2}, {0.0f, 0.0f} },
		{ { m_length / 2, 0.0f,         m_length / 2}, {1.0f, 1.0f} },
		{ { m_length / 2, m_length / 2, m_length / 2}, {1.0f, 0.0f} },

		// 後ろ
		{ { m_length / 2, 0.0f,         -m_length / 2}, {0.0f, 1.0f} },
		{ { m_length / 2, m_length / 2, -m_length / 2}, {0.0f, 0.0f} },
		{ {-m_length / 2, 0.0f,         -m_length / 2}, {1.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2, -m_length / 2}, {1.0f, 0.0f} },

		// 左
		{ {-m_length / 2, 0.0f,         -m_length / 2}, {0.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2, -m_length / 2}, {0.0f, 0.0f} },
		{ {-m_length / 2, 0.0f,          m_length / 2}, {1.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2,  m_length / 2}, {1.0f, 0.0f} },

		// 右
		{ {m_length / 2, 0.0f,          m_length / 2}, {0.0f, 1.0f} },
		{ {m_length / 2, m_length / 2,  m_length / 2}, {0.0f, 0.0f} },
		{ {m_length / 2, 0.0f,         -m_length / 2}, {1.0f, 1.0f} },
		{ {m_length / 2, m_length / 2, -m_length / 2}, {1.0f, 0.0f} },

		// 上
		{ {m_length / 2,  m_length / 2, -m_length / 2}, {1.0f, 0.0f} },
		{ {m_length / 2,  m_length / 2,  m_length / 2}, {1.0f, 1.0f} },
		{ {-m_length / 2, m_length / 2, -m_length / 2}, {0.0f, 0.0f} },
		{ {-m_length / 2, m_length / 2,  m_length / 2}, {0.0f, 1.0f} },

	};

	void* pVertices;
	m_vertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	// 頂点構造体のデータを頂点バッファにコピー
	memcpy(pVertices, vertices, sizeof(vertices));
	m_vertexBuffer->Unlock();
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
	pDevice->SetFVF(FVF_SKYBOX);											// 頂点フォーマットの設定

	// 描画
	for (int count = 0; count < 5; count++)
	{
		shader->m_effectPoint->SetTexture(shader->m_texture1Handle, m_texture[count]);	// テクスチャの設定
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, count * 4, 2);
	}
}