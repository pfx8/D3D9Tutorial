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
		m_woman->m_pos + D3DXVECTOR3(0.0f, 30.0f, -200.0f),	// Eye
		m_woman->m_pos + D3DXVECTOR3(0.0f, 8.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f));		// Up
	m_camera->SetViewMatrix();	// ビューイング変換
	m_camera->SetProjMatrix();	// プロジェクション変換
	m_camera->SetViewport();	// ビューポートを設定

	// シェーダー
	m_shader = new Shader;
	m_shader->LoadEffectFile();

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
// シンーの更新
//
//*****************************************************************************
void Scene00::Update()
{
	//m_camera->UpdateAt(m_car1->m_pos);
	m_camera->Update();	// カメラ更新
	m_woman->Update(&m_woman->m_pos, &m_woman->m_speed, &m_worldMatrix);	// キャラクター更新
	m_fieldStone->SetWorldMatrix(m_worldMatrix);	// フィールド更新

	
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

		// テクニックを設定
		m_shader->m_effectPoint->SetTechnique(m_shader->m_techniqueHandle);

		UINT passNum = 0;
		m_shader->m_effectPoint->Begin(&passNum, 0);
		for (int count = 0; count < passNum; count++)
		{
			m_shader->m_effectPoint->BeginPass(0);	// 各パスから描画する

			D3DXMATRIX WVPmatrix = m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
			m_shader->m_effectPoint->SetMatrix(m_shader->m_WVPMatrixHandle, &WVPmatrix);

			//m_shader->m_effectPoint->SetVector(m_shader->m_lightingHandle, &D3DXVECTOR4(0.0f, -1.0f, 0.0f, 0.0f));

			m_fieldStone->Draw(m_shader);	// (On Shader)
			//m_fieldStone->Draw();	// (No Shader)

			m_shader->m_effectPoint->EndPass();
		}
		m_shader->m_effectPoint->End();

		//m_woman->Draw(m_shader->m_vertexShader, m_shader->m_vertexDcl);
		
		char str[256];	// デバッグメッセージ
		//sprintf(str, _T("X %.2f, Y %.2f Z %.2f"), m_fieldStone->m_pos.x, m_fieldStone->m_pos.y, m_fieldStone->m_pos.z);
		sprintf(str, _T("X %.2f, Y %.2f Z %.2f"), m_camera->m_posEye.x, m_camera->m_posEye.y, m_camera->m_posEye.z);
		m_message->DrawMessage(str);

		GetDevice()->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	GetDevice()->Present(NULL, NULL, NULL, NULL);
}