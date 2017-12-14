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
	// シェーダー
	m_shader = new Shader;
	m_shader->LoadEffectFile();

	// 光方向ベクトルを設定
	m_shader->m_effectPoint->SetVector(m_shader->m_lightingHandle, &D3DXVECTOR4(-1.0f, 4.0f, -1.0f, 0.0f));

	// フィールド
	m_fieldStone = new Plane();
	m_fieldStone->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR2(10, 10));
	m_resourcesManager->LoadTexture("fieldTransparent", &m_fieldStone->m_fieldTexture);
	
	// 主人公
	m_hero = new Character();
	m_hero->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_resourcesManager->LoadMesh("woman", m_hero->m_model);

	// カメラ
	m_camera = new Camera();
	m_camera->InitCamera(
		m_hero->m_pos + D3DXVECTOR3(0.0f, 8.0f, 12.0f),	// Eye
		m_hero->m_pos + D3DXVECTOR3(0.0f, 6.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f));					// Up
	m_camera->SetViewMatrix();	// ビューイング変換
	m_camera->SetProjMatrix();	// プロジェクション変換
	m_camera->SetViewport();		// ビューポートを設定

	std::cout << "[State] BoundingBox: " << std::boolalpha << m_hero->m_boundingBox->m_isBoundingBoxDraw << std::endl;
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
	RELEASE_CLASS_POINT(m_hero);		// 車
	RELEASE_CLASS_POINT(m_camera);	// カメラ
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene00::Update()
{
	Control();	// 各操作の更新

	m_camera->UpdateAt(m_hero->m_pos + +D3DXVECTOR3(0.0f, 6.0f, 0.0f));	// カメラ更新
	m_camera->Update(&m_hero->m_directionVector);

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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// バックバッファ＆Ｚバッファのクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(153, 153, 153, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(GetDevice()->BeginScene()))
	{
		//---------------------------------------
		// エフェクトに基づいてレンダリング
		//---------------------------------------
		// BasicShader
		{
			m_fieldStone->SetWorldMatrix(m_worldMatrix);	// ワールド変換

			m_shader->m_effectPoint->SetTechnique(m_shader->m_basicShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数
			m_shader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_shader->m_effectPoint->BeginPass(0);

				D3DXMATRIX WVPmatrix = m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
				m_shader->m_effectPoint->SetMatrix(m_shader->m_WVPMatrixHandle, &WVPmatrix);	// WVPマトリックス
				m_fieldStone->Draw(m_shader);

				m_shader->m_effectPoint->EndPass();
			}
			m_shader->m_effectPoint->End();
		}

		// NoTextureShader
		{
			m_hero->SetWorldMatrix(&m_worldMatrix);	// ワールド変換

			m_shader->m_effectPoint->SetTechnique(m_shader->m_noTextureShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数
			m_shader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_shader->m_effectPoint->BeginPass(0);

				D3DXMATRIX WVPmatrix = m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
				m_shader->m_effectPoint->SetMatrix(m_shader->m_WVPMatrixHandle, &WVPmatrix);	// WVPマトリックス
				m_hero->Draw(m_shader);

				m_shader->m_effectPoint->EndPass();
			}
			m_shader->m_effectPoint->End();
		}

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}


//*****************************************************************************
//
// 操作関数
//
//*****************************************************************************
void Scene00::Control()
{
	// プレーヤー操作更新
	if (GetKeyboardPress(DIK_A))	// key A
	{
		m_hero->m_pos.x -= m_hero->m_directionVector.x;
	}
	if (GetKeyboardPress(DIK_D))	// key D
	{
		m_hero->m_pos.x += m_hero->m_directionVector.x;
	}
	if (GetKeyboardPress(DIK_W))	// key W
	{
		m_hero->m_pos.z += m_hero->m_directionVector.x;
	}
	if (GetKeyboardPress(DIK_S))	// key S
	{
		m_hero->m_pos.z -= m_hero->m_directionVector.x;
	}

	//　カメラ操作更新
	if (GetKeyboardPress(DIK_J))	// key J
	{
		m_camera->RotationVecUp(1.5f / 180.0f * D3DX_PI);
	}
	if (GetKeyboardPress(DIK_L))	// key L
	{
		m_camera->RotationVecUp(-1.5f / 180.0f * D3DX_PI);
	}

	// プレーヤーからカメラまでの半径操作更新
	if (GetKeyboardPress(DIK_UP))	// key UP
	{
		m_camera->isAtToEyeVectorMoreLong(true);
	}
	if (GetKeyboardPress(DIK_DOWN))	// key DOWN
	{
		m_camera->isAtToEyeVectorMoreLong(false);
	}

	// バウンディングボックス操作更新
	if (GetKeyboardTrigger(DIK_Q))	// key Q
	{
		m_hero->m_boundingBox->m_isBoundingBoxDraw = !m_hero->m_boundingBox->m_isBoundingBoxDraw;	// バウンディングボックスをコントロール
		std::cout << "[State] BoundingBox: " << std::boolalpha << m_hero->m_boundingBox->m_isBoundingBoxDraw << std::endl;
	}
}