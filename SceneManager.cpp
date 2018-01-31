//*****************************************************************************
//
// シーンマネジャー処理 [SceneManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SceneManager.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
SceneManager::SceneManager()
{
	// 最初はタイトルから
	m_sceneTitle = new SceneTitle;
	m_scene00 = new Scene00;
	m_sceneEnding = new SceneEnding;

	// 最初のシーンを設定
	m_sceneState = SS_Title;

	// シーンリストを作る
	m_sceneList[SS_Title] = m_sceneTitle;
	m_sceneList[SS_Run] = m_scene00;
	m_sceneList[SS_Ending] = m_sceneEnding;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SceneManager::~SceneManager()
{
	RELEASE_CLASS_POINT(m_sceneList[m_sceneState]);
}

//*****************************************************************************
//
// シーンを選択する
//
//*****************************************************************************
void SceneManager::ChooseScene(SCENESTATE state)
{
	// まずは前のシーンを削除する
	//RELEASE_CLASS_POINT(m_sceneList[m_sceneState]);

	switch (state)
	{
	case SS_Title:
		m_sceneState = SS_Title;
		m_sceneTitle->SetRenderState();	// レンダリング状態を設定

		break;
	case SS_Run:
		m_sceneState = SS_Run;
		m_scene00->SetRenderState();

		break;
	case SS_Ending:
		m_sceneState = SS_Ending;

		break;
	default:
		break;
	}
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void SceneManager::Update()
{
	m_sceneList[m_sceneState]->Update();		// シンー01更新
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

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		// 次のシーンに進み
		if (m_sceneState == SS_Title)
			ChooseScene(SS_Run);
		if (m_sceneState == SS_Ending)
			ChooseScene(SS_Title);
	}

	if (GetKeyboardTrigger(DIK_BACK) && m_sceneState == SS_Run)
	{
		// 戻るメニュー
		ChooseScene(SS_Title);
	}

	// テスト用キー、ゲームが終了
	if (GetKeyboardTrigger(DIK_RSHIFT) && m_sceneState == SS_Run)
	{
		// ゲームをクリアすると、Endingへ行く
		ChooseScene(SS_Ending);
	}
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void SceneManager::Draw()
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(162, 236, 238, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		m_sceneList[m_sceneState]->Draw();

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}