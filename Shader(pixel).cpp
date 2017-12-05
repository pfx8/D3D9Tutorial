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
	m_pixelShader = NULL;
	m_constTable = NULL;

	m_ratioHandle = NULL;
	m_samp0Handle = NULL;
	m_samp1Handle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_pixelShader);
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

	// ピクセルモードチェック
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* shaderBuffer = NULL;	// シェーダーバッファ
	ID3DXBuffer* errorBuffer = NULL;	// エラーバッファ

	D3DXCompileShaderFromFile(
		"Shader/PixelShader.hlsl",	//シェーダーファイルパス
		0,				// デフォルト設定
		0,				// デフォルト設定
		"Main",			// シェーダーの入り口関数
		"ps_2_0",			// コンパイルターゲットを含む文字列へのポインタ
		D3DXSHADER_DEBUG,	// ンパイル オプション
		&shaderBuffer,	// シェーダーバッファ
		&errorBuffer,		// エラーバッファ
		&m_constTable);	// 定数表

	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] シェーダーが読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	// ピクセルシェーダーを作る
	pDevice->CreatePixelShader((DWORD*)shaderBuffer->GetBufferPointer(), &m_pixelShader);

	// シェーダーファイル中の変数を取得
	m_ratioHandle = m_constTable->GetConstantByName(0, "Scalar");	// 混ざり比率
	m_samp0Handle = m_constTable->GetConstantByName(0, "Samp0");	// サンプラー0
	m_samp1Handle = m_constTable->GetConstantByName(0, "Samp1");	// サンプラー1

	//
	UINT count;
	m_constTable->GetConstantDesc(m_samp0Handle, &m_samp0Desc, &count);	// 
	m_constTable->GetConstantDesc(m_samp1Handle, &m_samp1Desc, &count);	// 

	m_constTable->SetDefaults(pDevice);	// デフォルト設定

	return S_OK;
}