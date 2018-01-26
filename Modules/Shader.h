//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "../Engine.h"

class Shader
{
private:
	virtual HRESULT LoadEffectFile();		// 頂点シェーダーファイルを読み込む
	virtual void GetShaderParameter();		// シェーダー中の変数を取得

public:
	ID3DXEffect* m_effectPoint;		// エフェクト(複数レンダリング保存される)

	D3DXHANDLE   m_shaderHandle;	// エフェクトのテクニック
	D3DXHANDLE   m_WMatrixHandle;	// ワールド変換行列
	D3DXHANDLE   m_VPMatrixHandle;	// ビューイング変換とプロジェクション変換行列
	D3DXHANDLE   m_textureHandle;	// テクスチャ
	D3DXHANDLE   m_alphaHandle;		// カラーのアルファ値

	Shader();
	~Shader();

	void InitShader();				// シェーダーを初期化する
};

#endif // !_SHADER_H_
