﻿//*****************************************************************************
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
	this->sceneTitle = new SceneTitle;
	this->scene00 = new Scene00;
	this->sceneEnding = new SceneEnding;

	// 最初のシーンを設定
	this->sceneState = SS_Title;
	
	// 音楽
	this->bgm = LoadSound(BGM_TITLE);
	PlaySound(this->bgm, E_DS8_FLAG_LOOP);

	// シーンリストを作る
	this->sceneList[SS_Title] = this->sceneTitle;
	this->sceneList[SS_Run] = this->scene00;
	this->sceneList[SS_Ending] = this->sceneEnding;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
SceneManager::~SceneManager()
{
	RELEASE_CLASS_POINT(this->sceneList[this->sceneState]);
	RELEASE_POINT(this->bgm);
}

//*****************************************************************************
//
// シーンを選択する
//
//*****************************************************************************
void SceneManager::ChooseScene(SCENESTATE state)
{
	switch (state)
	{
	case SS_Title:
		this->sceneState = SS_Title;
		this->sceneTitle->SetRenderState();	// レンダリング状態を設定

		// 音楽
		this->bgm->Release();
		this->bgm = LoadSound(BGM_TITLE);
		PlaySound(this->bgm, E_DS8_FLAG_LOOP);

		break;
	case SS_Run:
		this->sceneState = SS_Run;
		this->scene00->SetRenderState();

		// 音楽
		this->bgm->Release();
		this->bgm = LoadSound(BGM_GAME);
		PlaySound(this->bgm, E_DS8_FLAG_LOOP);

		break;
	case SS_Ending:
		this->sceneState = SS_Ending;

		// 音楽
		this->bgm->Release();
		this->bgm = LoadSound(BGM_END);
		PlaySound(this->bgm, E_DS8_FLAG_LOOP);

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
	this->sceneList[this->sceneState]->Update();		// シンー01更新
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

	bool isButton = false;
	isButton = (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_OPTIONS));
	if (isButton)
	{
		// 次のシーンに進み
		if (this->sceneState == SS_Title)
		{
			ChooseScene(SS_Run);
			this->scene00->InitScene00();
		}
		if (this->sceneState == SS_Ending)
			ChooseScene(SS_Title);
	}

	isButton = (GetKeyboardTrigger(DIK_BACK) || IsButtonTriggered(0, BUTTON_SHARE));
	if (isButton && this->sceneState == SS_Run)
	{
		// 戻るメニュー
		ChooseScene(SS_Title);
	}

	// テスト用キー、ゲームが終了
	if (this->scene00->ship->HP == 0 && this->sceneState == SS_Run)
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
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(122, 122, 122, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		this->sceneList[this->sceneState]->Draw();

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}