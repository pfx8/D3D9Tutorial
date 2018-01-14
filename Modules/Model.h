//*****************************************************************************
//
// モデル処理 [Model.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "Material.h"
#include "..\Engine.h"
#include "..\Shader\CelShader.h"


//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Model
{
private:

public:
	LPD3DXMESH			m_meshPoint;		// メッシュ情報へのポインタ
	LPDIRECT3DTEXTURE9*	m_meshTexturePoint;	// テクスチャマネジメント
	Material*			m_material;			// マテリアル情報へのポインタ

	Model();
	~Model();

	void DrawModel(CelShader* celShader);	// モデルを描画する
};

#endif // !_MODEL_H_

