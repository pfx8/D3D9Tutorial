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
	IDirect3DVertexShader9* m_vertexShader;		// 頂点シェーダーポインタ
	IDirect3DVertexDeclaration9* m_vertexDecl;	// 頂点宣言
	ID3DXConstantTable* m_constTable;			// 定数表

	D3DXHANDLE m_ScalarHandle;			// モーフィング計算する数値
	D3DXHANDLE m_WVPMatrixHandle;		// ワールドマトリックスハンドル
	D3DXHANDLE m_LightDirectionHandle;	// カラーマトリックスハンドル

	Shader();
	~Shader();

	HRESULT LoadShaderFile();				// シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
