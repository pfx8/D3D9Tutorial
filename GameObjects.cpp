//=============================================================================
//
// ゲーム資源処理クラス [GameObjects.cpp]
// Author : リョウ　カンシン
//
//=============================================================================
#include "GameObjects.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
GameObjects::GameObjects()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GameObjects::~GameObjects()
{

}

void GameObjects::SetExample(ExampleType mode)
{
	switch (mode)
	{
	case ET_Vertex:
		InitEMVer();
		break;
	case ET_Light:
		InitEMLig();
		break;
	case ET_SampleMesh:
		break;
	default:
		break;
	}
}

bool GameObjects::GetStatus(void)
{
	return m_Status;
}

void GameObjects::InitEMVer(void)
{
	// 頂点バッファを初期化
	if (FAILED(GetDevice()->CreateVertexBuffer(8 * sizeof(Vertex_3D), 0, FVF_VERTEX, D3DPOOL_DEFAULT,
		GetVertexBuffer(), NULL)))
	{
		m_Status = false;
	}


	// 頂点インデックスバッファを初期化
	if (FAILED(GetDevice()->CreateIndexBuffer(36 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT,
		GetIndexBuffer(), NULL)))
	{
		m_Status = false;
	}

	//顶点数据的设置，
	Vertex_3D Vertices[] =
	{
		{ -20.0f, 20.0f, -20.0f,  D3DCOLOR_XRGB(10, 10, 10) },
		{ -20.0f, 20.0f, 20.0f,  D3DCOLOR_XRGB(10, 10, 10) },
		{ 20.0f, 20.0f, 20.0f,  D3DCOLOR_XRGB(10, 10, 10) },
		{ 20.0f, 20.0f, -20.0f,  D3DCOLOR_XRGB(10, 10, 10) },
		{ -20.0f, -20.0f, -20.0f, D3DCOLOR_XRGB(10, 10, 10) },
		{ -20.0f, -20.0f, 20.0f, D3DCOLOR_XRGB(10, 10, 10) },
		{ 20.0f, -20.0f, 20.0f, D3DCOLOR_XRGB(10, 10, 10) },
		{ 20.0f, -20.0f, -20.0f, D3DCOLOR_XRGB(10, 10, 10) },

	};

	//填充顶点缓存
	VOID* pVertices;
	if (FAILED((*(GetVertexBuffer()))->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
	{
		m_Status = false;
	}
	memcpy(pVertices, Vertices, sizeof(Vertices));
	(*(GetVertexBuffer()))->Unlock();

	// 填充索引数据
	WORD *pIndices = NULL;
	(*(GetIndexBuffer()))->Lock(0, 0, (void**)&pIndices, 0);

	// 顶面
	pIndices[0] = 0, pIndices[1] = 1, pIndices[2] = 2;
	pIndices[3] = 0, pIndices[4] = 2, pIndices[5] = 3;
	// 正面
	pIndices[6] = 0, pIndices[7] = 3, pIndices[8] = 7;
	pIndices[9] = 0, pIndices[10] = 7, pIndices[11] = 4;
	// 左侧面
	pIndices[12] = 0, pIndices[13] = 4, pIndices[14] = 5;
	pIndices[15] = 0, pIndices[16] = 5, pIndices[17] = 1;
	// 右侧面
	pIndices[18] = 2, pIndices[19] = 6, pIndices[20] = 7;
	pIndices[21] = 2, pIndices[22] = 7, pIndices[23] = 3;
	// 背面
	pIndices[24] = 2, pIndices[25] = 5, pIndices[26] = 6;
	pIndices[27] = 2, pIndices[28] = 1, pIndices[29] = 5;
	// 底面
	pIndices[30] = 4, pIndices[31] = 6, pIndices[32] = 5;
	pIndices[33] = 4, pIndices[34] = 7, pIndices[35] = 6;

	(*(GetIndexBuffer()))->Unlock();
}

void GameObjects::InitEMLig(void)
{

}