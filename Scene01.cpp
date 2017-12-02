//*****************************************************************************
//
// ShaderTutorial処理 [Scene01.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene01.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene01::Scene01()
{	
	
	SetSceneName("ShaderTutorial");	// シーンに名前をつける
	Scene::ConsoleMessage(GetSceneName());	// コンソールを表示

	// カメラ
	m_camera = new Camera;
	m_camera->InitCamera(
		D3DXVECTOR3(0.0f, 100.0f, -400.0f),	// Eye
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// Up
	m_camera->SetViewMatrix();	// ビューイング変換
	m_camera->SetProjMatrix();	// プロジェクション変換
	m_camera->SetViewport();	// ビューポートを設定
	
	// シェーダー
	m_shader = new Shader;
	m_shader->LoadShaderFile();

	// イルカ
	m_dolphin = new Character;
	m_dolphin->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_resourcesManager->LoadMesh("dolphin1", m_dolphin->m_meshPoint);

	m_dolphin2 = new Character;
	m_dolphin2->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_resourcesManager->LoadMesh("dolphin2", m_dolphin2->m_meshPoint);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene01::~Scene01()
{
	// クラスポインタ
	// カメラ
	RELEASE_CLASS_POINT(m_camera);
	// シェーダー
	RELEASE_CLASS_POINT(m_shader);
	// イルカ
	RELEASE_CLASS_POINT(m_dolphin);
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene01::Update()
{
	m_camera->Update();
	m_camera->UpdateAt(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_dolphin->Update();
	m_dolphin->SetWorldMatrix(m_mtxWorld);
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene01::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(153, 153, 153, 1), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		// シェーダーにWVPMatrixを渡す
		D3DXMATRIX matWVP = m_mtxWorld * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
		m_shader->m_constTable->SetMatrix(pDevice, m_shader->m_WVPMatrixHandle, &matWVP);

		// Scalar計算
		float DolphinTimeFactor = (float)(timeGetTime() % 501) / 250.0f;
		float Scalar = (DolphinTimeFactor <= 1.0f) ? DolphinTimeFactor : (2.0f - DolphinTimeFactor);
		m_shader->m_constTable->SetVector(pDevice, m_shader->m_ScalarHandle, &D3DXVECTOR4(1.0f - Scalar, Scalar, 0.0f, 0.0f));

		// 頂点シェーダー設定
		pDevice->SetVertexShader(m_shader->m_vertexShader);

		// 頂点シェーダ宣言設定
		pDevice->SetVertexDeclaration(m_shader->m_vertexDecl);

		// 目標メッシュの頂点バッファをストリーム番号1にする
		IDirect3DVertexBuffer9* Stream1 = NULL;
		m_dolphin->m_meshPoint->m_meshPoint->GetVertexBuffer(&Stream1);
		pDevice->SetStreamSource(1, Stream1, 0, D3DXGetFVFVertexSize(m_dolphin->m_meshPoint->m_meshPoint->GetFVF()));
		RELEASE_POINT(Stream1);

		// 目標メッシュの頂点バッファをストリーム番号1にする
		IDirect3DVertexBuffer9* Stream2 = NULL;
		m_dolphin2->m_meshPoint->m_meshPoint->GetVertexBuffer(&Stream2);
		pDevice->SetStreamSource(1, Stream2, 0, D3DXGetFVFVertexSize(m_dolphin2->m_meshPoint->m_meshPoint->GetFVF()));
		RELEASE_POINT(Stream2);

		m_dolphin->Draw(m_shader->m_vertexShader, m_shader->m_vertexDecl);

		pDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	pDevice->Present(NULL, NULL, NULL, NULL);
}