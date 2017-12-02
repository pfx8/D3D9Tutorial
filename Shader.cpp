//*****************************************************************************
//
// Shader処理 [Shader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Shader.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Shader::Shader()
{
	m_vertexShader = NULL;
	m_vertexDecl = NULL;
	m_constTable = NULL;

	m_WVPMatrixHandle = NULL;
	m_LightDirectionHandle = NULL;
	m_ScalarHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_vertexShader);
	RELEASE_POINT(m_vertexDecl);
	RELEASE_POINT(m_constTable);

}

//*****************************************************************************
//
// シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::LoadShaderFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ID3DXBuffer* shaderBuffer = NULL;	// シェーダーバッファ
	ID3DXBuffer* errorBuffer = NULL;	// エラーバッファ

	D3DVERTEXELEMENT9 MorphMeshDecl[] =
	{
		// ストリーム番号1
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },

		// ストリーム番号2
		{ 1,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 1 },
		{ 1, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   1 },
		D3DDECL_END()
	};

	HRESULT hr = D3DXCompileShaderFromFile(
		"Shader/Vertex.hlsl",
		0,
		0,
		"SetVertex",		// シェーダーの入り口関数
		"vs_1_1",			// コンパイル ターゲットを含む文字列へのポインタ???
		D3DXSHADER_DEBUG,	// ンパイル オプション
		&shaderBuffer,	// シェーダーバッファ
		&errorBuffer,		// エラーバッファ
		&m_constTable);	// 定数表
	
	if (FAILED(hr))	// エラーをチェック
	{
		std::cout << "Error: Shader->LoadShader" << std::endl;
		return E_FAIL;
	}

	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "Error: Shader->errorBuffer" << std::endl;
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}


	pDevice->CreateVertexShader((DWORD*)shaderBuffer->GetBufferPointer(), &m_vertexShader);	// 頂点シェーダーを作成する
	pDevice->CreateVertexDeclaration(MorphMeshDecl, &m_vertexDecl);	// デバイスおよび頂点要素から頂点シェーダ宣言を作成する
	RELEASE_POINT(shaderBuffer);	// シェーダーバッファをリリース

	// シェーダーファイル中の変数を取得
	m_WVPMatrixHandle = m_constTable->GetConstantByName(0, "WVPMatrix");	// WVPマトリックス
	m_LightDirectionHandle = m_constTable->GetConstantByName(0, "LightDirection");	// 乱反射光
	m_ScalarHandle = m_constTable->GetConstantByName(0, "Scalar");	// モーフィング数値

	m_constTable->SetVector(pDevice, m_LightDirectionHandle, &D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f));
	m_constTable->SetDefaults(pDevice);	// デフォルト設定

	return S_OK;
}