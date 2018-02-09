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
	void GetShaderParameter();		// シェーダーを使うために、各設定をする

public:
	ID3DXEffect*	m_effectPoint;		// エフェクト(複数レンダリング保存される)
	D3DXHANDLE		m_celShaderHandle;	// エフェクトのテクニック
	D3DXHANDLE		m_WMatrixHandle;	// ワールド変換
	D3DXHANDLE		m_VPMatrixHandle;	// ビューイング変換とプロジェクション変換
	D3DXHANDLE		m_lightingHandle;	// 光の方向
	D3DXHANDLE		m_typeHandle;		// オブジェクトの種類を判断

	CelShader();
	~CelShader();

	void InitShader();						// シェーダーを初期化する
};

#endif // !_CEL_SHADER_H_
