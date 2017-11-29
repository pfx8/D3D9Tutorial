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
	m_shaderBuffer = NULL;
	m_errorBuffer = NULL;
	m_vertexShader = NULL;
	m_constTable = NULL;

	m_WVPMatrixHandle = NULL;
	m_colorHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	SAFE_RELEASE_POINT(m_shaderBuffer);
	SAFE_RELEASE_POINT(m_errorBuffer);
	SAFE_RELEASE_POINT(m_vertexShader);
	SAFE_RELEASE_POINT(m_constTable);
}

//*****************************************************************************
//
// シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::LoadShaderFile()
{
	HRESULT hr = D3DXCompileShaderFromFile(
		"Shader/Basic.hlsl",
		0,
		0,
		"SetColor",		// シェーダーの入り口関数
		"vs_1_0",			// コンパイル ターゲットを含む文字列へのポインタ???
		D3DXSHADER_DEBUG,	// ンパイル オプション
		&m_shaderBuffer,	// シェーダーバッファ
		&m_errorBuffer,	// エラーバッファ
		&m_constTable);	// 定数表

	if (m_errorBuffer)		// エラーを出す
	{
		std::cout << "Error: Shader->m_errorBuffer" << std::endl;
		SAFE_RELEASE_POINT(m_errorBuffer);
		return E_FAIL;
	}

	if (FAILED(hr))	// エラーを出す
	{
		std::cout << "Error: Shader->LoadShader" << std::endl;
		return E_FAIL;
	}

	// 頂点シェーダーができた
	hr = GetDevice()->CreateVertexShader((DWORD*)m_shaderBuffer->GetBufferPointer(), &m_vertexShader);

	if (FAILED(hr))	// エラーを出す
	{
		std::cout << "Error: Shader->CreateVertexShader" << std::endl;
		return E_FAIL;
	}

	SAFE_RELEASE_POINT(m_shaderBuffer);	// シェーダーバッファをリリース

	// シェーダーファイル中の変数を取得
	m_WVPMatrixHandle = m_constTable->GetConstantByName(0, "WVPMatrix");	// WVPマトリックス
	m_colorHandle = m_constTable->GetConstantByName(0, "color");		// 頂点カラー

	m_constTable->SetDefaults(GetDevice());	// デフォルト設定

	return S_OK;
}