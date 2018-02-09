//*****************************************************************************
//
// 画面座標用シェーダー [RHWShader.h]
// 
// 説明:タイトルとエンディングの描画
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RHW_SHADER_H_
#define _RHW_SHADER_H_

#include "../Modules/Shader.h"

class RHWShader : public Shader
{
private:
	HRESULT LoadEffectFile();		// 頂点シェーダーファイルを読み込む
	void GetShaderParameter();		// シェーダーを使うために、各設定をする

public:
	ID3DXEffect*	effectPoint;		// エフェクト(複数レンダリング保存される)
	D3DXHANDLE		RHWShaderHandle;	// エフェクトのテクニック
	D3DXHANDLE		textureHandle;	// テクスチャ

	RHWShader();
	~RHWShader();

	void InitShader();	// シェーダーを初期化する
};

#endif // !_RHW_SHADER_H_
