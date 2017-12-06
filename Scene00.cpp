//*****************************************************************************
//
// D3DTutorial処理 [Scene00.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene00.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene00::Scene00()
{
	SetSceneName("D3DTutorial");	// シーンに名前をつける
	Scene::ConsoleMessage(GetSceneName());	// コンソールを表示

	// フィールド
	m_fieldStone = new Plane();
	m_fieldStone->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR2(100, 100));
	m_resourcesManager->LoadTexture("fieldGrass", &m_fieldStone->m_fieldTexture);
	
	// 車
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

	// シェーダー
	m_shader = new Shader;
	m_shader->LoadVertexShaderFile();

	std::cout << "[State] BoundingBox: " << std::boolalpha << m_woman->m_boundingBox->m_isBoundingBoxDraw << std::endl;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene00::~Scene00()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(m_fieldStone);	// フィールド
	RELEASE_CLASS_POINT(m_woman);	// 車
	RELEASE_CLASS_POINT(m_camera);	// カメラ
}

//*****************************************************************************
//
// プレーヤー操作更新
//
//*****************************************************************************
void Scene00::UpdatePlayer(D3DXVECTOR3* Pos, D3DXVECTOR3* Speed)
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
		m_woman->m_boundingBox->m_isBoundingBoxDraw = !m_woman->m_boundingBox->m_isBoundingBoxDraw;
		std::cout << "[State] BoundingBox: " << std::boolalpha << m_woman->m_boundingBox->m_isBoundingBoxDraw << std::endl;
	}
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene00::Update()
{
	
	m_camera->Update();	// カメラ視点移動

	UpdatePlayer(&m_woman->m_pos, &m_woman->m_speed);	// プレーヤー操作更新
	m_woman->SetWorldMatrix(m_mtxWorld);
	
	m_fieldStone->SetWorldMatrix(m_mtxWorld);

	//m_camera->UpdateAt(m_car1->m_pos);

	// 当たり判定
	//if (m_car1->CheckHitBB(m_car2))
	//{
	//	// 移動
	//	m_car2->Move();
	//}
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene00::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	GetDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		m_fieldStone->Draw(m_shader->m_pixelShader, m_shader->m_samp0Desc);
		m_woman->Draw(m_shader->m_vertexShader, m_shader->m_vertexDcl);
		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}