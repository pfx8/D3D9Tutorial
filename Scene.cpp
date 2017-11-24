﻿//*****************************************************************************
//
// シーン処理 [Scene.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene::Scene()
{	
	// リソース
	m_resourcesManager = new ResourcesManager();

	// フィールド
	m_FieldStone = new Field();
	
	// 車
	m_car1 = new Character();
	m_car2 = new Character();

	// ライト
	m_light = new Light();

	// カメラ
	m_camera = new Camera();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene()
{
	// クラスポインタ
	// リソース
	SAFE_RELEASE_CLASS_POINT(m_resourcesManager);

	// フィールド
	SAFE_RELEASE_CLASS_POINT(m_FieldStone);

	// 車
	SAFE_RELEASE_CLASS_POINT(m_car1);
	SAFE_RELEASE_CLASS_POINT(m_car2);

	// ライト
	SAFE_RELEASE_CLASS_POINT(m_light);

	// カメラ
	SAFE_RELEASE_CLASS_POINT(m_camera);
}

//*****************************************************************************
//
// シンーの初期化
//
// up:blenderから読み込む予定
//
//*****************************************************************************
void Scene::InitScene(std::string name)
{
	// 名前を決める
	m_sceneName = name;

	// シンーによって資源を読み込む
	LoadScene();

	// フィールド
	m_FieldStone->InitField(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR2(100, 100),
		GetResourcesManager()->SetTexture("FieldGrass"));

	// 車
	/*for (int count = 0; count < m_carNum; count++)
	{
		m_car[count]->InitCharacter(
			D3DXVECTOR3(0.0f + count * 50, 0.0f, 0.0f),
			GetResourcesManager()->SetTexture("NULL"),
			"data/MODEL/car000.x");
	}*/
	m_car1->InitCharacter(
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		GetResourcesManager()->SetTexture("NULL"),
		"data/MODEL/car000.x");
	m_car2->InitCharacter(
		D3DXVECTOR3(0.0f + 50, 0.0f, 0.0f),
		GetResourcesManager()->SetTexture("NULL"),
		"data/MODEL/car001.x");

	// ライト
	// 無し

	// カメラを初期化
	m_camera->InitCamera(
		D3DXVECTOR3(0.0f, 150.0f, -200.0f),	// Eye
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f),		// Up
		*m_car1->GetPosition());			// 注視点のPos

}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene::Update()
{
	// プレーヤー操作更新

	UpdatePlayer((D3DXVECTOR3*)m_car1->GetMember("pos"), (D3DXVECTOR3*)m_car1->GetMember("speed"));

	// フィールド更新
	// 無し

	// ライト更新
	m_light->Update();

	// カメラ視点移動
	m_camera->Update();

	// 当たり判定
	if (m_car1->CheckHitBB(m_car2))
	{
		// 移動
		m_car2->Move();
	}
}

//*****************************************************************************
//
// プレーヤー操作更新
//
//*****************************************************************************
void Scene::UpdatePlayer(D3DXVECTOR3* Pos, D3DXVECTOR3* Speed)
{
	if (GetKeyboardPress(DIK_A))	// key A
	{
		Pos->x -= Speed->x;
	}
	if (GetKeyboardPress(DIK_D))	// key D
	{
		Pos->x += Speed->x;
	}
	if (GetKeyboardPress(DIK_W))	// key W
	{
		Pos->z += Speed->x;
	}
	if (GetKeyboardPress(DIK_S))	// key S
	{
		Pos->z -= Speed->x;
	}

	if (GetKeyboardTrigger(DIK_Q))	// key Q
	{
		m_car1->m_BoundingBoxON = !m_car1->m_BoundingBoxON;
		m_car2->m_BoundingBoxON = !m_car2->m_BoundingBoxON;
	}
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	GetDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 1), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{

		//// レンダリングデフォルトモード
		//GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); // 省略可

		// 1.
		// キャラクターをワールド変換
		m_car1->SetWorldMatrix(m_mtxWorld);
		// キャラクターを描画する
		m_car1->Draw();

		// 2.
		// キャラクターをワールド変換
		m_car2->SetWorldMatrix(m_mtxWorld);
		// キャラクターを描画する
		m_car2->Draw();

		// ビューポートを設定
		m_camera->setViewport();

		// フィールドをワールド変換して描画する
		m_FieldStone->SetWorldMatrix(m_mtxWorld);
		m_FieldStone->Draw();

		// ビューイング変換
		m_camera->setViewMatrix();

		// プロジェクション変換
		m_camera->setProjMatrix();

		// キャラクターの座標インフォメーション、括弧の中はなん行目
		m_car1->PosToMessageAndMessageDraw(0);
		m_car2->PosToMessageAndMessageDraw(1);

		// カメラの座標インフォメーション
		//g_camera->PosToMessageAndMessageDraw(2);

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
HRESULT Scene::LoadSceneFile(string name)
{
	// コンソールにメッセージを出す
	cout << "Loading " << name << endl;

	// 読み込みオブジェクトを作る
	ifstream fin;
	
	// ファイルを読み込み
	fin.open(name);

	// 読み込みは失敗した場合
	if (fin.fail())
	{
		// コンソールにメッセージを出す
		cout << "エラー[ 読み込み失敗 ]" << endl;
		return E_FAIL;
	}
	else
	{
		// コンソールにメッセージを出す
		cout << name << " ok!" << endl;
		char PathTemp[100];
		while (!fin.eof())
		{
			fin.getline(PathTemp, 100);
			cout << PathTemp << endl;
		}

		// 未完成
	}
}

//*****************************************************************************
//
// ファイルからシンーの資源を読み込み
//
//*****************************************************************************
void Scene::LoadScene()
{
	m_resourcesManager->InitTextureList();
}

//*****************************************************************************
//
// リソースマネジメントを取得
//
//*****************************************************************************
ResourcesManager* Scene::GetResourcesManager()
{
	return m_resourcesManager;
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
std::string Scene::GetSceneName()
{
	return m_sceneName;
}