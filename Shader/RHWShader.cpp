//*****************************************************************************
//
// 画面座標用シェーダー [RHWShader.h]
// 
// 説明:タイトルとエンディングの描画
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "RHWShader.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
RHWShader::RHWShader()
{
	this->effectPoint = NULL;
	this->RHWShaderHandle = NULL;
	this->textureHandle = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
RHWShader::~RHWShader()
{
	RELEASE_POINT(this->effectPoint);
}

//*****************************************************************************
//
// シェーダーを初期化
//
//*****************************************************************************
void RHWShader::InitShader()
{
	LoadEffectFile();
	GetShaderParameter();
}

//*****************************************************************************
//
// 頂点シェーダーファイルを読み込む
//
//*****************************************************************************
HRESULT RHWShader::LoadEffectFile()
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
						"Shader/RHWShader.fx",	// エフェクトファイルの名前
						0,
						0,
						D3DXSHADER_DEBUG,
						0,
						&this->effectPoint,		// エフェクトポインタ
						&errorBuffer);		// エラー情報


	if (errorBuffer)	// エラーをチェック
	{
		std::cout << "[Error] Shader/RHWShader.fx が読み込めない" << std::endl;	// エラーメッセージ
		std::cout << "[Information] " << (char*)errorBuffer->GetBufferPointer() << std::endl;	// エラーメッセージ
		RELEASE_POINT(errorBuffer);
		return E_FAIL;
	}

	std::cout << "[Information] Loading Shader<RHWShader> Success!" << std::endl;
	return S_OK;
}

//*****************************************************************************
//
// シェーダーを使うために、各設定をする
//
//*****************************************************************************
void RHWShader::GetShaderParameter()
{
	// レンダリングのテクニックを取得
	this->RHWShaderHandle = this->effectPoint->GetTechniqueByName("RHWRender");

	// シェーダー中のグローバル変数を取得
	this->textureHandle = this->effectPoint->GetParameterByName(0, "tex");
}