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
	ID3DXBuffer* m_shaderBuffer;			// シェーダーバッファ
	ID3DXBuffer* m_errorBuffer;				// エラーバッファ
	IDirect3DVertexShader9* m_vertexShader;	// 頂点シェーダーポインタ
	ID3DXConstantTable* m_constTable;		// 定数表
	D3DXHANDLE m_WVPMatrixHandle;			// ワールドマトリックスハンドル
	D3DXHANDLE m_colorHandle;				// カラーマトリックスハンドル

	Shader();
	~Shader();

	HRESULT LoadShaderFile();				// シェーダーファイルを読み込む
};

#endif // !_SHADER_H_
