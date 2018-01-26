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

	// スカイボックス
	//m_skyBox = new SkyBox;
	//m_skyBox->InitSkyBox(50.0f);
	//m_resourcesManager->LoadTexture("skybox", &m_skyBox->m_texture);


	// フィールド
	m_fieldStone = new Plane;
	m_fieldStone->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXVECTOR2(50, 50));
	m_resourcesManager->LoadTexture("fieldSea", &m_fieldStone->m_texture);
	
	// 主人公
	m_ship = new Character;
	m_ship->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f));
	m_ship->m_boundingBox->InitBox(4, 7, 8, 0.1f);	// バウンディングボックスを初期化
	m_resourcesManager->LoadMesh("ship2", m_ship->m_model); // モデルを初期化

	// 敵
	m_enemyShip = new Enemy[ENEMY_MAX];
	for (int count = 0; count < ENEMY_MAX; count++)
	{
		D3DXVECTOR3 temp = D3DXVECTOR3(float(rand() % 150), 0.0f, float(rand() % 120));
		if (rand() % 1 == 0 && rand() % 1 == 0)
		{
			temp.x *= -1;
		}
		if (rand() % 1 == 0 && rand() % 1 != 0)
		{
			temp.z *= -1;
		}
		m_enemyShip[count].InitEnemy(temp);
		m_resourcesManager->LoadMesh("ship2", m_enemyShip[count].m_model);
		m_enemyShip[count].m_boundingBox->InitBox(4, 7, 8, 0.1f);	// バウンディングボックスを初期化
		m_enemyShip[count].Trans((rand() % 80) / 180.0f * D3DX_PI);		// 向きを決める
	}

	// 弾
	m_bullet = new Bullet[BULLET_MAX];
	for (int count = 0; count < BULLET_MAX; count++)
	{
		m_resourcesManager->LoadMesh("ball", m_bullet[count].m_model);
	}

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

	RELEASE_CLASS_ARRY_POINT(m_enemyShip); // エネミー
	RELEASE_CLASS_ARRY_POINT(m_bullet); // エネミー
}

//*****************************************************************************
//
// レンダリング状態を設定
//
//*****************************************************************************
void Scene00::SetRenderState()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// レンダーステートパラメータの設定
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// 光を使う
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			// αブレンドを行う
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

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
	m_fieldStone->Update();	// 波の更新

	// 弾移動更新
	for (int count = 0; count < BULLET_MAX; count++)
	{
		if (m_bullet[count].m_isUse == true)
		{
			m_bullet[count].BulletMove(D3DXVECTOR2(200.0f, 200.0f));
		}
	}

	// 敵移動更新
	for (int count = 0; count < ENEMY_MAX; count++)
	{
		if (m_enemyShip[count].m_isLife == true)
		{
			m_enemyShip[count].EnemyMove(D3DXVECTOR2(150.0f, 150.0f));
		}
	}

	// 敵の攻撃
	for (int count = 0; count < ENEMY_MAX; count++)
	{
		if (m_enemyShip[count].EnemyAttack(m_ship) == true && m_enemyShip[count].m_isAttack == false)
		{
			for (int count2 = 0; count2 < BULLET_MAX; count2++)
			{
				if (m_bullet[count2].m_isUse == false)
				{
					m_bullet[count2].InitBulletByCharacter(m_enemyShip[count].m_pos, m_enemyShip[count].m_lookVector, false); // プレーヤーによって弾を初期化
					m_enemyShip[count].m_isAttack = true;
					break;
				}
			}
		}
	}

	// 弾と敵の当たり判定
	for (int count = 0; count < BULLET_MAX; count++)
	{
		if (m_bullet[count].m_isUse == true && m_bullet[count].m_isEnemyBullet == false)
		{
			for (int count2 = 0; count2 < ENEMY_MAX; count2++)
			{
				if (m_enemyShip[count2].m_isLife == true && m_enemyShip[count2].m_isAttack == false)
				{
					if (CheckBB((m_bullet + count), (m_enemyShip + count2)))
					{
						m_bullet[count].m_isUse = false;
						m_enemyShip[count2].m_isLife = false;
						m_enemyShip[count2].m_time = 0.016f * 120;
					}
				}
			}
		}
	}

	//m_celShader->UpdateLight(m_light->m_directionlight);	// 光ベクトル更新
	
	// 揺れる状況
	m_ship->Update(m_fieldStone->m_waveAngle);
	for (int count = 0; count < ENEMY_MAX; count++)
	{
		m_enemyShip[count].Update(m_fieldStone->m_waveAngle);
	}
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
		// フィールド
		{
			// テクニックを設定
			m_shader->m_shaderHandle = m_shader->m_effectPoint->GetTechniqueByName("RenderWithTextrue");
			m_shader->m_effectPoint->SetTechnique(m_shader->m_shaderHandle);
			
			// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
			m_shader->m_effectPoint->SetMatrix(m_shader->m_WMatrixHandle, &m_fieldStone->m_worldMatrix);	
			D3DXMATRIX fieldVPmatrix = m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
			m_shader->m_effectPoint->SetMatrix(m_shader->m_VPMatrixHandle, &fieldVPmatrix);
			
			// テクスチャ、アルファ値の設定
			m_shader->m_effectPoint->SetTexture(m_shader->m_textureHandle, m_fieldStone->m_texture);
			m_shader->m_effectPoint->SetFloat(m_shader->m_alphaHandle, 1.0f);
			
			// 描画
			UINT passNum = 0;
			m_shader->m_effectPoint->Begin(&passNum, 0);
			// 各パスを実行する
			for (int count = 0; count < passNum; count++)
			{
				m_shader->m_effectPoint->BeginPass(0);
				m_fieldStone->Draw();

				m_shader->m_effectPoint->EndPass();
			}
			m_shader->m_effectPoint->End();
		}

		// スカイボックス
		//{
		//	// テクニックを設定
		//	m_shader->m_effectPoint->SetTechnique(m_shader->m_basicShaderHandle);

		//	// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
		//	SetWorldMatrix(&m_skyBox->m_worldMatrix);
		//	m_shader->m_effectPoint->SetMatrix(m_shader->m_WMatrixHandle, &m_skyBox->m_worldMatrix);
		//	D3DXMATRIX skyBoxVPmatrix = m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
		//	m_shader->m_effectPoint->SetMatrix(m_shader->m_VPMatrixHandle, &skyBoxVPmatrix);

		//	// テクスチャの設定
		//	m_shader->m_effectPoint->SetTexture(m_shader->m_texture1Handle, m_skyBox->m_texture);

		//	// 描画
		//	UINT passNum = 0;
		//	m_shader->m_effectPoint->Begin(&passNum, 0);
		//	// 各パスを実行する
		//	for (int count = 0; count < passNum; count++)
		//	{
		//		m_shader->m_effectPoint->BeginPass(0);
		//		m_skyBox->Draw(m_shader);

		//		m_shader->m_effectPoint->EndPass();
		//	}
		//	m_shader->m_effectPoint->End();
		//}

		// オブジェクト種類番号
		int ship = 0, enemy = 1, cannon = 2, boundingBox = 3;

		// ship
		{
			// モデル
			m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定
			UINT passNum = 0;	// パスの数

			m_ship->SetWorldMatrix();
			D3DXMATRIX shipWVPmatrix = m_ship->m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
			m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &shipWVPmatrix);	// WVPマトリックス

			m_celShader->m_effectPoint->SetInt(m_celShader->m_typeHandle, ship);

			m_celShader->m_effectPoint->Begin(&passNum, 0);
			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
			{
				m_celShader->m_effectPoint->BeginPass(count);

				m_ship->Draw(m_celShader);

				m_celShader->m_effectPoint->EndPass();
			}
			m_celShader->m_effectPoint->End();

			// バウンディングボックス
			if (m_ship->m_boundingBox->m_isBoundingBoxDraw == true)
			{
				// テクニックを設定
				m_shader->m_shaderHandle = m_shader->m_effectPoint->GetTechniqueByName("RenderWithoutTextrue");
				m_shader->m_effectPoint->SetTechnique(m_shader->m_shaderHandle);

				// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
				m_shader->m_effectPoint->SetMatrix(m_shader->m_WMatrixHandle, &m_ship->m_worldMatrix);
				D3DXMATRIX VPmatrix = m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
				m_shader->m_effectPoint->SetMatrix(m_shader->m_VPMatrixHandle, &VPmatrix);

				// アルファ値の設定(テクスチャ無し)
				m_shader->m_effectPoint->SetFloat(m_shader->m_alphaHandle, 0.5f);

				// 描画
				UINT passNum = 0;
				m_shader->m_effectPoint->Begin(&passNum, 0);
				// 各パスを実行する
				for (int count = 0; count < passNum; count++)
				{
					m_shader->m_effectPoint->BeginPass(0);

					m_ship->m_boundingBox->Draw();

					m_shader->m_effectPoint->EndPass();
				}
				m_shader->m_effectPoint->End();
			}		
		}

		// エネミー
		{
			for (int count1 = 0; count1 < ENEMY_MAX; count1++)
			{
				if (m_enemyShip[count1].m_isLife == true)
				{
					m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定
					UINT passNum = 0;	// パスの数

					m_enemyShip[count1].SetWorldMatrix();
					D3DXMATRIX enemyWVPmatrix = m_enemyShip[count1].m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
					m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &enemyWVPmatrix);	// WVPマトリックス

					bool isShip = true;
					m_celShader->m_effectPoint->SetInt(m_celShader->m_typeHandle, enemy);

					m_celShader->m_effectPoint->Begin(&passNum, 0);
					for (int count = 0; count < passNum; count++)	// 各パスによって描画する
					{
						m_celShader->m_effectPoint->BeginPass(count);

						m_enemyShip[count1].Draw(m_celShader);

						m_celShader->m_effectPoint->EndPass();
					}
					m_celShader->m_effectPoint->End();
				}
			}
		}

		// 弾
		{
			for (int count1 = 0; count1 < BULLET_MAX; count1++)
			{
				if (m_bullet[count1].m_isUse == true)
				{
					m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定
					UINT passNum = 0;	// パスの数

					m_bullet[count1].SetWorldMatrix();
					D3DXMATRIX bulletWVPmatrix = m_bullet[count1].m_worldMatrix * m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
					m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WVPMatrixHandle, &bulletWVPmatrix);	// WVPマトリックス

					bool isShip = false;
					m_celShader->m_effectPoint->SetInt(m_celShader->m_typeHandle, cannon);

					m_celShader->m_effectPoint->Begin(&passNum, 0);
					for (int count = 0; count < passNum; count++)	// 各パスによって描画する
					{
						m_celShader->m_effectPoint->BeginPass(count);

						m_bullet[count1].Draw(m_celShader);

						m_celShader->m_effectPoint->EndPass();
					}
					m_celShader->m_effectPoint->End();
				}
			}
		}

		if (m_isGameStart == false)
		{
			
		}
		
		// デッバグメッセージ
		m_ship->PosToMessageAndMessageDraw(0);
		m_light->message(4);

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
		// プレーヤー操作 逆
		if (GetKeyboardTrigger(DIK_S))	// 前に進む
		{
			//m_camera->m_posEye += m_ship->MoveAlongVecLook(-0.5f);
			//m_ship->MoveAlongVecLook(-0.25f);
			m_ship->ChangeLever(LL_FRONT);
		}
		if (GetKeyboardTrigger(DIK_W))	// 後ろに進む
		{
			//m_camera->m_posEye += m_ship->MoveAlongVecLook(-0.5f);
			//m_ship->MoveAlongVecLook(-0.25f);
			m_ship->ChangeLever(LL_BACK);
		}

		if (GetKeyboardPress(DIK_A))	// 左回転
		{
			// 更新キャラクターをカメラの回転角度
			m_ship->RotationVecUp(0.5f / 180.0f * D3DX_PI);
			//m_camera->UpdateAngle(-0.5f / 180.0f * D3DX_PI);
		}
		else if (GetKeyboardPress(DIK_D))	// 右回転
		{
			// 更新キャラクターをカメラの回転角度
			m_ship->RotationVecUp(-0.5f / 180.0f * D3DX_PI);
			//m_camera->UpdateAngle(0.5f / 180.0f * D3DX_PI);
		}

		//　カメラ操作
		if (GetKeyboardPress(DIK_J))	// 左回転
		{
			m_camera->RotationVecUp(1.0f / 180.0f * D3DX_PI);
		}
		else if (GetKeyboardPress(DIK_L))	// 右回転
		{
			m_camera->RotationVecUp(-1.0f / 180.0f * D3DX_PI);
		}
		else if (GetKeyboardPress(DIK_I))	// カメラを上に移動
		{
			m_camera->MoveAlongVecLook(-0.5f);
		}
		else if (GetKeyboardPress(DIK_K))	// カメラを下に移動
		{
			m_camera->MoveAlongVecLook(0.5f);
		}

		// ライト操作更新
		//if (GetKeyboardPress(DIK_Z))	// key Z
		//{
		//	m_light->RotationY(0.5f / 180.0f * D3DX_PI);
		//}
		//if (GetKeyboardPress(DIK_X))	// key X
		//{
		//	m_light->RotationY(-0.5f / 180.0f * D3DX_PI);
		//}

		// プレーヤー攻撃
		if (GetKeyboardTrigger(DIK_SPACE))	// 攻撃
		{
			for (int count = 0; count < BULLET_MAX; count++)
			{
				if (m_bullet[count].m_isUse == false)
				{
					m_bullet[count].InitBulletByCharacter(m_ship->m_pos, m_ship->m_lookVector, true); // プレーヤーによって弾を初期化
					break;
				}
			}
		}

		// バウンディングボックス操作更新
		if (GetKeyboardTrigger(DIK_Q))	// バウンディングボックスをコントロール
		{
			// プレーヤー
			m_ship->m_boundingBox->m_isBoundingBoxDraw = !m_ship->m_boundingBox->m_isBoundingBoxDraw;	// バウンディングボックスをコントロール
			
			// エネミー
			for (int count = 0; count < ENEMY_MAX; count++)
			{
				m_enemyShip[count].m_boundingBox->m_isBoundingBoxDraw = !m_enemyShip[count].m_boundingBox->m_isBoundingBoxDraw;
			}
			
			// 弾
			for (int count = 0; count < BULLET_MAX; count++)
			{
				m_bullet[count].m_boundingBox->m_isBoundingBoxDraw = !m_bullet[count].m_boundingBox->m_isBoundingBoxDraw;
			}
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

//*****************************************************************************
//
// 当たり判定
//
//*****************************************************************************
bool Scene00::CheckBB(Bullet* bullet, Enemy* enemy)
{
	// 弾
	D3DXVECTOR3 bulletPos = bullet->m_pos;
	D3DXVECTOR3 bulletBoxSize = bullet->m_boundingBox->m_size;
	// エネミー
	D3DXVECTOR3 enemyPos = enemy->m_pos;
	D3DXVECTOR3 enemyBoxSize = enemy->m_boundingBox->m_size;

	if (
		bulletPos.x + bulletBoxSize.x / 2 > enemyPos.x - enemyBoxSize.x / 2 &&
		bulletPos.x - bulletBoxSize.x / 2 < enemyPos.x + enemyBoxSize.x / 2 &&
		bulletPos.y - bulletBoxSize.y / 2 < enemyPos.y + enemyBoxSize.y / 2 &&
		bulletPos.y + bulletBoxSize.y / 2 > enemyPos.y - enemyBoxSize.y / 2 &&
		bulletPos.z + bulletBoxSize.z / 2 > enemyPos.z - enemyBoxSize.z / 2 &&
		bulletPos.z - bulletBoxSize.z / 2 < enemyPos.z + enemyBoxSize.z / 2
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}