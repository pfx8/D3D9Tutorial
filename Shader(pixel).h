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
	LPDIRECT3DPIXELSHADER9 m_pixelShader;	// ピクセルシェーダーポインタ
	ID3DXConstantTable* m_constTable;		// 定数表
	LPDIRECT3DVERTEXSHADER9 m_vertexShader;	// 頂点シェーダー
	
	D3DXHANDLE m_ratioHandle;	// 混ざり比率
	D3DXHANDLE m_samp0Handle;	// サンプラー0
	D3DXHANDLE m_samp1Handle;	// サンプラー1
	D3DXHANDLE m_lightingHandle;	// 光方向

	D3DXCONSTANT_DESC m_samp0Desc;	// サンプラー定数テーブル
	D3DXCONSTANT_DESC m_samp1Desc;	// サンプラー定数テーブル

	Shader();
	~Shader();

	HRESULT LoadShaderFile();				// シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
