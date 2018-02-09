//*****************************************************************************
//
// エンディング処理 [SceneEnding.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_ENDING_H_
#define _SCENE_ENDING_H_

#include "Modules\Scene.h"
#include "Shader\RHWShader.h"
#include "Engine.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneEnding : public Scene
{
private:
	RHWShader*						RHWshader;

public:
	ResourcesManager*				resourcesManager;	// リソースマネジメント
	IDirect3DVertexDeclaration9*	vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// 頂点インデックスバッファ
	LPDIRECT3DTEXTURE9				texture;	// フィールドテクスチャ
	
	SceneEnding();
	~SceneEnding();

	HRESULT MakeVertexDecl();	// 頂点作成
	void Draw();
};

#endif // !_SCENE_SceneEnding_H_

