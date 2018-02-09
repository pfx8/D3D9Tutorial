//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "CelShader.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
CelShader::CelShader()
{
	m_effectPoint = NULL;
	m_celShaderHandle = NULL;
	m_WMatrixHandle = NULL;
	m_VPMatrixHandle = NULL;
	m_lightingHandle = NULL;
	//m_textureHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
CelShader::~CelShader()
{
	RELEASE_POINT(m_effectPoint);
}

//*****************************************************************************
//
// シェーダーを初期化
//
//*****************************************************************************
void CelShader::InitShader()
{
	LoadEffectFile();
	GetShaderParameter();
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT CelShader::LoadEffectFile()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DCAPS9 caps;
	pDevice->GetDeviceCaps(&caps);
	if (caps.PixelShaderVersion < D3DPS_VERSION(1, 1))	// ピクセル機能チェック
	{
		std::cout << "[Error]Not Support PixelShader Failed!" << std::endl;
	}

	ID3DXBuffer* errorBuffer = NULL;		// エラーバッファ
	D3DXCreateEffectFromFile(pDevice,
						"Shader/CelShader.fx",	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&m_effectPoint,		// エフェクトポインタ
						&errorBuffer);		// エラー情報


	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] Shader/CelShader.fx が読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<CelShader> Success!" << std::endl;
	return S_OK;
}

//*****************************************************************************
//
// シェーダーを使うために、各設定をする
//
//*****************************************************************************
void CelShader::GetShaderParameter()
{
	// レンダリングのテクニックを取得
	m_celShaderHandle = m_effectPoint->GetTechniqueByName("CelShader");
	//m_outLineHandle = m_effectPoint->GetTechniqueByName("Outline");

	// シェーダー中のグローバル変数を取得
	m_WMatrixHandle = m_effectPoint->GetParameterByName(0, "WMatrix");
	m_VPMatrixHandle = m_effectPoint->GetParameterByName(0, "VPMatrix");
	m_lightingHandle = m_effectPoint->GetParameterByName(0, "LightDirection");
	m_typeHandle = m_effectPoint->GetParameterByName(0, "type");
	//m_textureHandle = m_effectPoint->GetParameterByName(0, "Tex");

}