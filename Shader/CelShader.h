//*****************************************************************************
//
// トゥ―ンシェーダー処理 [CelShader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CEL_SHADER_H_
#define _CEL_SHADER_H_

#include "../Modules/Shader.h"

class CelShader : public Shader
{
private:
	HRESULT LoadEffectFile();					// 頂点シェーダーファイルを読み込む
	void GetShaderTechniqueAndParameter();		// シェーダーを使うために、各設定をする

public:
	ID3DXEffect* m_effectPoint;		// エフェクト(複数レンダリング保存される)
	D3DXHANDLE	m_celShaderHandle;	// エフェクトのテクニック
	D3DXHANDLE	m_WVPMatrixHandle;	// 変換行列
	D3DXHANDLE	m_lightingHandle;		// 光の方向
	D3DXHANDLE	m_changeMatrixHandle;	// 変更行列
	//D3DXHANDLE	m_textureHandle;		// テクスチャ

	CelShader();
	~CelShader();

	void InitShader();						// シェーダーを初期化する
	void UpdateLight(D3DXVECTOR3 direction);	// 更新ライトベクトル
};

#endif // !_CEL_SHADER_H_
