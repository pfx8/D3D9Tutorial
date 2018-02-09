//*****************************************************************************
//
// タイトル処理 [SceneTitle.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

#include "Modules\Scene.h"
#include "Shader\RHWShader.h"
#include "Engine.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class SceneTitle : public Scene
{
private:
	RHWShader*						RHWshader;

public:
	ResourcesManager*				resourcesManager;	// リソースマネジメント
	IDirect3DVertexDeclaration9*	vertexDecl;	// 頂点シェーダー宣言
	LPDIRECT3DVERTEXBUFFER9			vertexBuffer;	// 頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9			indexBuffer;	// 頂点インデックスバッファ
	LPDIRECT3DTEXTURE9				texture;	// フィールドテクスチャ
	
	SceneTitle();
	~SceneTitle();

	HRESULT MakeVertexDecl();	// 頂点作成
	void Draw();
};

#endif // !_SCENE_TITLE_H_

