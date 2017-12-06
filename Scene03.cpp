//*****************************************************************************
//
// Effect [Scene03.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene03.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene03::Scene03()
{	
	SetSceneName("PixelShader");	// シーンに名前をつける
	Scene::ConsoleMessage(GetSceneName());	// コンソールを表
	
	// シェーダー
	m_shader = new Shader;
	m_shader->LoadEffectFile();

	// テストモデル
	m_woman = new Character();
	m_woman->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_resourcesManager->LoadMesh("woman", m_woman->m_mesh);

	// カメラ
	m_camera = new Camera();
	m_camera->InitCamera(
		m_woman->m_pos + D3DXVECTOR3(0.0f, 10.0f, -15.0f),	// Eye
		m_woman->m_pos + D3DXVECTOR3(0.0f, 8.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// Up
	m_camera->SetViewMatrix();	// ビューイング変換
	m_camera->SetProjMatrix();	// プロジェクション変換
	m_camera->SetViewport();	// ビューポートを設定
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene03::~Scene03()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(m_camera);	// カメラ
	RELEASE_CLASS_POINT(m_shader);	// シェーダー
	RELEASE_CLASS_POINT(m_woman);	// テストモデル
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene03::Update()
{
	m_camera->Update();
	m_camera->UpdateAt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene03::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(153, 153, 153, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		D3DXMATRIX WVPMatrix = m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
		m_shader->m_effectPoint->SetMatrix(m_shader->m_WVPMatrixHandle, &WVPMatrix);

		m_woman->Draw();

		pDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	pDevice->Present(NULL, NULL, NULL, NULL);
}