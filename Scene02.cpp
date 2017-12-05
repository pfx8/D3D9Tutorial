//*****************************************************************************
//
// PixelShader [Scene02.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene02.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene02::Scene02()
{	
	SetSceneName("PixelShader");	// シーンに名前をつける
	Scene::ConsoleMessage(GetSceneName());	// コンソールを表示

	// カメラ
	m_camera = new Camera;
	m_camera->InitCamera(
		D3DXVECTOR3(0.0f, 200.0f, -200.0f),	// Eye
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// Up
	m_camera->SetViewMatrix();	// ビューイング変換
	m_camera->SetProjMatrix();	// プロジェクション変換
	m_camera->SetViewport();	// ビューポートを設定
	
	// シェーダー
	m_shader = new Shader;
	m_shader->LoadShaderFile();

	// 平面1
	m_plane = new Plane;
	m_plane->InitPlaneDT(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f));
	m_resourcesManager->LoadTexture("1032", &m_plane->m_fieldTexture);

	// 平面2
	m_plane2 = NULL;
	m_resourcesManager->LoadTexture("1033", &m_plane2);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene02::~Scene02()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(m_camera);	// カメラ
	RELEASE_CLASS_POINT(m_shader);	// シェーダー
	RELEASE_CLASS_POINT(m_plane);	// 平面１
	RELEASE_CLASS_POINT(m_plane2);	// 平面2
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene02::Update()
{
	m_camera->Update();
	m_camera->UpdateAt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene02::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(153, 153, 153, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		// 混ざり比率を設定
		D3DXVECTOR4 scalar(0.5f, 0.5f, 0.0f, 1.0f);
		m_shader->m_constTable->SetVector(pDevice, m_shader->m_ratioHandle, &scalar);
		pDevice->SetPixelShader(m_shader->m_pixelShader);	// ピクセルシェーダー設定
		m_plane->Draw(m_plane2, m_shader->m_samp0Desc, m_shader->m_samp1Desc);

		pDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	pDevice->Present(NULL, NULL, NULL, NULL);
}