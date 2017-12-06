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
	m_effectPoint = NULL;
	
	m_WVPMatrixHandle = NULL;
	m_lightingHandle = NULL;
	m_techniqueHandle = NULL;
	m_textureHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(m_effectPoint);
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::LoadEffectFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ピクセル機能チェック
	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* errorBuffer = NULL;	// エラーバッファ

	D3DXCreateEffectFromFile(pDevice,
						"Effect.txt",	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&m_effectPoint,	// エフェクトポインタ
						&errorBuffer);	// エラー情報


	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] エフェクトが読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	// エフェクトのテクニックを設定
	m_techniqueHandle = m_effectPoint->GetTechniqueByName("T0");

	// シェーダー中のグローバル変数を取得
	m_WVPMatrixHandle = m_effectPoint->GetParameterByName(0, "WVPMatrix");
	m_lightingHandle = m_effectPoint->GetParameterByName(0, "LightDirection");
	m_textureHandle = m_effectPoint->GetParameterByName(0, "Tex");

	return S_OK;
}