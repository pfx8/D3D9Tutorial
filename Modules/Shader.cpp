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
	this->effectPoint = NULL;
	
	this->WMatrixHandle = NULL;
	this->VPMatrixHandle = NULL;
	this->shaderHandle = NULL;
	this->textureHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Shader::~Shader()
{
	RELEASE_POINT(this->effectPoint);
}

//*****************************************************************************
//
// シェーダーを初期化
//
//*****************************************************************************
void Shader::InitShader()
{
	LoadEffectFile();
	GetShaderParameter();
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT Shader::LoadEffectFile()
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
						"Shader/BasicShader.fx",	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effectPoint,		// エフェクトポインタ
						&errorBuffer);		// エラー情報


	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] Shader/BasicShader.fx が読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<BasicShader> Success!" << std::endl;

	return S_OK;
}

//*****************************************************************************
//
// シェーダー中の変数を取得
//
//*****************************************************************************
void Shader::GetShaderParameter()
{
	this->WMatrixHandle  = this->effectPoint->GetParameterByName(0, "WMatrix");
	this->VPMatrixHandle = this->effectPoint->GetParameterByName(0, "VPMatrix");
	this->textureHandle  = this->effectPoint->GetParameterByName(0, "tex");
	this->alphaHandle    = this->effectPoint->GetParameterByName(0, "alpha");
}