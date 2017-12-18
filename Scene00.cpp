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
	m_shader->InitShader();

	m_celShader = new CelShader;
	m_celShader->InitShader();

	// ライト
	m_light = new Light;
	D3DXVECTOR4 tempLight = D3DXVECTOR4(m_light->m_directionlight.x, m_light->m_directionlight.y, m_light->m_directionlight.z, 1.0f);
	m_celShader->m_effectPoint->SetVector(m_celShader->m_lightingHandle, &tempLight);

	// フィールド
	m_fieldStone = new Plane;
	m_fieldStone->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(4, 4));
	m_resourcesManager->LoadTexture("fieldTransparent", &m_fieldStone->m_fieldTexture);
	
	// 主人公
	m_hero = new Character;
	m_hero->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_resourcesManager->LoadMesh("woman", m_hero->m_model);

	// カメラ
	m_camera = new Camera;
	m_camera->InitCamera(
		m_hero->m_pos + D3DXVECTOR3(0.0f, 8.0f, 12.0f),	// Eye
		m_hero->m_pos + D3DXVECTOR3(0.0f, 6.0f, 0.0f),		// At
		D3DXVECTOR3(0.0f, 1.0f, 0.0f));					// Up
	m_camera->SetViewMatrix();	// ビューイング変換
	m_camera->SetProjMatrix();	// プロジェクション変換
	//m_camera->SetViewport();		// ビューポートを設定


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
	RELEASE_CLASS_POINT(m_light);		// ライト
	RELEASE_CLASS_POINT(m_shader);	// ベーシックシェーダー
	RELEASE_CLASS_POINT(m_celShader);	// トゥ―ンシェーダー
}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void Scene00::SetRenderState()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//// レンダーステートパラメータの設定
	//GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング
	//GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	//GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	//GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	//// サンプラーステートパラメータの設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	//GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	//// テクスチャステージステートの設定
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	//GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	// Set the default render states
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// Set the default texture stage states
	//pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	// Set the default texture filters
	//pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene00::Update()
{
	Control();	// 各操作の更新

	m_camera->UpdateAt(m_hero->m_pos + D3DXVECTOR3(0.0f, 6.0f, 0.0f));	// カメラ更新
	m_camera->Update(&m_hero->m_directionVector);

	m_celShader->UpdateLight(m_light->m_directionlight);
	m_fieldStone->Update();

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
		D3DXMATRIX WVPmatrix = m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;

		//---------------------------------------
		// エフェクトに基づいてレンダリング
		//---------------------------------------
		// BasicShader
		{
			//m_fieldStone->SetWorldMatrix(m_worldMatrix);	// ワールド変換
			m_shader->m_effectPoint->SetMatrix(m_shader->m_WVPMatrixHandle, &WVPmatrix);	// WVPマトリックス

			m_shader->m_effectPoint->SetTechnique(m_shader->m_basicShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数
			m_shader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_shader->m_effectPoint->BeginPass(0);

				m_fieldStone->Draw(m_shader);

				m_shader->m_effectPoint->EndPass();
			}
			m_shader->m_effectPoint->End();
		}

		// CelShader
		{
			//m_hero->SetWorldMatrix(&m_worldMatrix);	// ワールド変換
			m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &WVPmatrix);	// WVPマトリックス

			m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数
			m_celShader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_celShader->m_effectPoint->BeginPass(count);

				m_hero->Draw(m_celShader);

				m_celShader->m_effectPoint->EndPass();
			}
			m_celShader->m_effectPoint->End();
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
		m_hero->RotationVecUp(1.5f / 180.0f * D3DX_PI);
	}
	if (GetKeyboardPress(DIK_D))	// key D
	{
		m_hero->RotationVecUp(-1.5f / 180.0f * D3DX_PI);
	}
	if (GetKeyboardPress(DIK_W))	// key W
	{
		m_hero->MoveAlongVecLook(-0.5f);
	}
	if (GetKeyboardPress(DIK_S))	// key S
	{
		m_hero->MoveAlongVecLook(0.5f);
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
	if (GetKeyboardPress(DIK_I))	// key I
	{
		m_camera->MoveAlongVecLook(-0.5f);
	}
	if (GetKeyboardPress(DIK_K))	// key K
	{
		m_camera->MoveAlongVecLook(0.5f);
	}

	// ライト操作更新
	if (GetKeyboardPress(DIK_Z))	// key Z
	{
		m_light->RotationY(0.5f / 180.0f * D3DX_PI);
	}
	if (GetKeyboardPress(DIK_X))	// key X
	{
		m_light->RotationY(-0.5f / 180.0f * D3DX_PI);
	}

	// バウンディングボックス操作更新
	if (GetKeyboardTrigger(DIK_Q))	// key Q
	{
		m_hero->m_boundingBox->m_isBoundingBoxDraw = !m_hero->m_boundingBox->m_isBoundingBoxDraw;	// バウンディングボックスをコントロール
		std::cout << "[State] BoundingBox: " << std::boolalpha << m_hero->m_boundingBox->m_isBoundingBoxDraw << std::endl;
	}
}