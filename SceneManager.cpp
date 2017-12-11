//*****************************************************************************
//
// シーンマネジャー処理 [SceneManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SceneManager.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SceneManager::SceneManager()
{
	ChooseScene();	// シーンを選択
	SetState();		// レンダリング状態を設定
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SceneManager::~SceneManager()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(m_scene);
}

//*****************************************************************************
//
// シーンを選択する
//
// Scene00 -> D3DTutorial
// Scene01 -> VertexShader
// Scene02 -> TextureShader
//*****************************************************************************
void SceneManager::ChooseScene()
{
	m_scene = new Scene00; // 初期化する
	SetState();	// レンダリング状態を設定
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void SceneManager::Update()
{
	m_scene->Update();		// シンー01更新
	ChangeRenderState();	// レンダリング状態更新
}

//*****************************************************************************
//
// レンダリング状態更新
//
//*****************************************************************************
void SceneManager::ChangeRenderState()
{
	// 塗りつぶしモード
	if (GetKeyboardPress(DIK_1))			// key 1
	{
		// ワイヤフレームを塗りつぶす
		GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (GetKeyboardPress(DIK_2))			// key 2
	{
		// 面を塗りつぶす
		GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	if (GetKeyboardPress(DIK_3))			// key 3
	{
		// バウンディングボックスを表示

	}
	if (GetKeyboardPress(DIK_4))			// key 4
	{
		// バウンディングボックスを消す

	}
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void SceneManager::Draw()
{
	m_scene->Draw();	// シンー01描画
}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void SceneManager::SetState()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// レンダーステートパラメータの設定
	//GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング
	//GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	//GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	//GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	//// サンプラーステートパラメータの設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	//// テクスチャステージステートの設定
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	// Set the default render states
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// Set the default texture stage states
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// Set the default texture filters
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
}