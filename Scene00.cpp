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
	m_fieldStone->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), D3DXVECTOR2(1, 1));
	m_resourcesManager->LoadTexture("fieldSea", &m_fieldStone->m_fieldTexture1);
	
	// 主人公
	m_ship = new Character;
	m_ship->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_resourcesManager->LoadMesh("ship", m_ship->m_model);

	// test
	m_test = new Character;
	m_test->InitCharacter(D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_resourcesManager->LoadMesh("car1", m_test->m_model);
	// test2
	m_test2 = new Character;
	m_test2->InitCharacter(D3DXVECTOR3(15.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_resourcesManager->LoadMesh("car2", m_test2->m_model);

	// カメラ
	m_camera = new Camera;
	m_camera->InitCameraByPlayer(m_ship);

	m_isGameStart = true;

	std::cout << "[State] BoundingBox: " << std::boolalpha << m_ship->m_boundingBox->m_isBoundingBoxDraw << std::endl;
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
	RELEASE_CLASS_POINT(m_ship);		// プレーヤー
	RELEASE_CLASS_POINT(m_camera);	// カメラ
	RELEASE_CLASS_POINT(m_light);		// ライト
	RELEASE_CLASS_POINT(m_shader);	// ベーシックシェーダー
	RELEASE_CLASS_POINT(m_celShader);	// トゥ―ンシェーダー

	// test
	RELEASE_CLASS_POINT(m_test);
	RELEASE_CLASS_POINT(m_test2);
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

	m_camera->UpdateByPlayer(m_ship);

	m_celShader->UpdateLight(m_light->m_directionlight);
	m_fieldStone->Update();

	//m_hero->Update(m_fieldStone->r);

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
			m_shader->m_effectPoint->SetTechnique(m_shader->m_basicShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数

			m_shader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_shader->m_effectPoint->BeginPass(0);

				D3DXMATRIX fieldWVPmatrix = m_fieldStone->m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
				m_shader->m_effectPoint->SetMatrix(m_shader->m_WVPMatrixHandle, &fieldWVPmatrix);	// WVPマトリックス
				m_fieldStone->Draw(m_shader);

				m_shader->m_effectPoint->EndPass();
			}
			m_shader->m_effectPoint->End();
		}

		// ship
		{
			m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数

			m_celShader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_celShader->m_effectPoint->BeginPass(count);

				m_ship->SetWorldMatrix();
				D3DXMATRIX shipWVPmatrix = m_ship->m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
				m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &shipWVPmatrix);	// WVPマトリックス
				m_ship->Draw(m_celShader);

				m_celShader->m_effectPoint->EndPass();
			}
			m_celShader->m_effectPoint->End();
		}

		// test
		{
			m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数

			m_celShader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_celShader->m_effectPoint->BeginPass(count);

				m_test->SetWorldMatrix();
				D3DXMATRIX testWVPmatrix = m_test->m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
				m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &testWVPmatrix);	// WVPマトリックス
				m_test->Draw(m_celShader);

				m_celShader->m_effectPoint->EndPass();
			}
			m_celShader->m_effectPoint->End();
		}

		// test2
		{
			m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数

			m_celShader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_celShader->m_effectPoint->BeginPass(count);

				m_test2->SetWorldMatrix();
				D3DXMATRIX test2WVPmatrix = m_test2->m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
				m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &test2WVPmatrix);	// WVPマトリックス
				m_test2->Draw(m_celShader);

				m_celShader->m_effectPoint->EndPass();
			}
			m_celShader->m_effectPoint->End();
		}

		// Outline
		/*{
			m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &WVPmatrix);	// WVPマトリックス

			m_celShader->m_effectPoint->SetTechnique(m_celShader->m_outLineHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数
			m_celShader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_celShader->m_effectPoint->BeginPass(count);

				m_hero->Draw(m_celShader);

				m_celShader->m_effectPoint->EndPass();
			}
			m_celShader->m_effectPoint->End();
		}*/

		if (m_isGameStart == false)
		{
			
		}
		//m_message->DrawMessage("光方向調整 [Z] [X]\nカメラ回転 [J] [L]\nモデル回転 [A] [D]\n近遠変換   [I] [K]\nバウンディングボックス ON/OFF [Q]");
		//m_message->DrawPosMessage("プレーヤー方向ベクトル: ", m_hero->m_directionVector, D3DXVECTOR2(0.0f, 18.0f));
		
		//m_ship->PosToMessageAndMessageDraw(0);
		m_camera->PosToMessageAndMessageDraw(0);
		m_ship->PosToMessageAndMessageDraw(2);
		m_test->PosToMessageAndMessageDraw(8);
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
	if (m_isGameStart == true)
	{
		// プレーヤー操作更新
		if (GetKeyboardPress(DIK_A))	// key A
		{
			m_ship->RotationVecUp(-1.5f / 180.0f * D3DX_PI);
		}
		if (GetKeyboardPress(DIK_D))	// key D
		{
			m_ship->RotationVecUp(1.5f / 180.0f * D3DX_PI);
		}
		if (GetKeyboardPress(DIK_W))	// key W
		{
			m_camera->m_posEye += m_ship->MoveAlongVecLook(-0.5f);
		}
		if (GetKeyboardPress(DIK_S))	// key S
		{
			m_camera->m_posEye -= m_ship->MoveAlongVecLook(0.5f);
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

		// 攻撃
		if (GetKeyboardPress(DIK_SPACE))	// key space
		{
			
		}

		// バウンディングボックス操作更新
		if (GetKeyboardTrigger(DIK_Q))	// key Q
		{
			m_ship->m_boundingBox->m_isBoundingBoxDraw = !m_ship->m_boundingBox->m_isBoundingBoxDraw;	// バウンディングボックスをコントロール
			std::cout << "[State] BoundingBox: " << std::boolalpha << m_ship->m_boundingBox->m_isBoundingBoxDraw << std::endl;
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_RETURN))	// key Enter
		{
			m_isGameStart = true;
		}
	}
}