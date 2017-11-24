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
	m_sceneD3D = new Scene00();	// シーン初期化

	ConsoleMessage();	// コンソール

	SetState();	// レンダリング状態を設定
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SceneManager::~SceneManager()
{
	// クラスポインタ
	// シーン
	SAFE_RELEASE_CLASS_POINT(m_sceneD3D);
}

//*****************************************************************************
//
// コンソールに表示するメッセージ
//
// 修正为可以新建场景，以及场景list
//
//*****************************************************************************
void SceneManager::ConsoleMessage()
{
	// コンソールにシンーの名前を出す
	cout << endl << "///////////////////////////////" << endl;
	cout << "// Scene : " << m_sceneD3D->GetSceneName() << endl;
	cout << "///////////////////////////////" << endl << endl;
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void SceneManager::Update()
{
	m_sceneD3D->Update();	// シーン更新

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
	m_sceneD3D->Draw();
}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void SceneManager::SetState()
{
	// レンダーステートパラメータの設定
	GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング
	GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
}