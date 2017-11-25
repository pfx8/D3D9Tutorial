//*****************************************************************************
//
// シーン01処理 [Scene01.cpp]
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
	// ライト
	m_light = new Light();

	// カメラ
	m_camera = new Camera();
	m_camera->InitCamera(
		D3DXVECTOR3(0.0f, 3.0f, -5.0f),		// Eye
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// Up

	// 名前をつける
	SetSceneName("ShaderTutorial");
	
	// シェーダー
	m_shader = new Shader();
	m_shader->LoadShaderFile();

	// ティーポット
	m_teapot = NULL;
	D3DXCreateTeapot(GetDevice(), &m_teapot, 0);
	D3DXCreateBox(GetDevice(), 200.0f, 200.0f, 200.0f, &m_box, 0);

	// コンソールを表示
	Scene::ConsoleMessage(GetSceneName());
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene01::~Scene01()
{
	m_box->Release();
	m_teapot->Release();

	// クラスポインタ
	// ライト
	SAFE_RELEASE_CLASS_POINT(m_light);
	// カメラ
	SAFE_RELEASE_CLASS_POINT(m_camera);
	// シェーダー
	SAFE_RELEASE_CLASS_POINT(m_shader);
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene01::Update()
{
	m_camera->Update();
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene01::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	GetDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 1), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		// ビューポートを設定
		m_camera->setViewport();
		// ビューイング変換
		m_camera->setViewMatrix();
		// プロジェクション変換
		m_camera->setProjMatrix();

		D3DXMATRIX matWorld, matView, matProj;
		GetDevice()->GetTransform(D3DTS_WORLD, &matWorld);
		GetDevice()->GetTransform(D3DTS_VIEW, &matView);
		GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);

		D3DXMATRIX matWVP = matWorld * matView * matProj;
		m_shader->m_constTable->SetMatrix(GetDevice(), m_shader->m_WVPMatrixHandle, &matWVP);	// シェーダーのWVPマトリックスを設定

		D3DXVECTOR4 color(1.0f, 1.0f, 0.0f, 1.0f);
		m_shader->m_constTable->SetVector(GetDevice(), m_shader->m_colorHandle, &color);		// シェーダーの頂点カラーを設定

		GetDevice()->SetVertexShader(m_shader->m_vertexShader);	// シェーダーを設定

		m_teapot->DrawSubset(0);	// ティーポット
		m_box->DrawSubset(0);

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}

//*****************************************************************************
//
// ファイル(blender)からシンーの資源を読み込み
//
//*****************************************************************************
//HRESULT Scene00::LoadSceneFile(string name)
//{
//	// コンソールにメッセージを出す
//	cout << "Loading " << name << endl;
//
//	// 読み込みオブジェクトを作る
//	ifstream fin;
//	
//	// ファイルを読み込み
//	fin.open(name);
//
//	// 読み込みは失敗した場合
//	if (fin.fail())
//	{
//		// コンソールにメッセージを出す
//		cout << "エラー[ 読み込み失敗 ]" << endl;
//		return E_FAIL;
//	}
//	else
//	{
//		// コンソールにメッセージを出す
//		cout << name << " ok!" << endl;
//		char PathTemp[100];
//		while (!fin.eof())
//		{
//			fin.getline(PathTemp, 100);
//			cout << PathTemp << endl;
//		}
//
//		// 未完成
//	}
//}