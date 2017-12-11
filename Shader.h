//*****************************************************************************
//
// Shader処理 [Shader.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SHADER_H_
#define _SHADER_H_

#include "Engine.h"

class Shader
{
private:

public:
	ID3DXEffect* m_effectPoint;	// エフェクト(複数レンダリング保存される)
	
	D3DXHANDLE m_techniqueHandle;	// エフェクトのテクニック

	D3DXHANDLE m_WVPMatrixHandle;	// 変換行列
	//D3DXHANDLE m_lightingHandle;	// 光の方向
	D3DXHANDLE m_textureHandle;		// テクスチャ

	Shader();
	~Shader();

	HRESULT LoadEffectFile();		// 頂点シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
