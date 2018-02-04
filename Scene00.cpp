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

	// ライト、光方向はデフォルトで(1, 0, 1)
	m_directionLight = new Light;
	m_celShader->m_effectPoint->SetValue("lightDir", &m_directionLight->m_light.Direction, sizeof(D3DXVECTOR3));
	m_celShader->m_effectPoint->SetValue("lightDiffuse", &m_directionLight->m_light.Diffuse, sizeof(D3DXCOLOR));
	m_celShader->m_effectPoint->SetValue("lightAmbient", &m_directionLight->m_light.Ambient, sizeof(D3DXCOLOR));
	m_celShader->m_effectPoint->SetValue("lightSpecular", &m_directionLight->m_light.Specular, sizeof(D3DXCOLOR));

	// スカイボックス
	m_skyBox = new SkyBox;
	m_skyBox->InitSkyBox(500.0f);
	m_resourcesManager->LoadTexture("skybox", &m_skyBox->m_texture);

	// フィールド
	m_fieldStone = new Plane;
	m_fieldStone->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(17.0f, 17.0f), D3DXVECTOR2(100, 100));
	m_resourcesManager->LoadTexture("fieldSea", &m_fieldStone->m_texture);
	
	// 主人公
	m_ship = new Character;
	m_ship->InitCharacter(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), 2);
	// 各モデルを初期化
	m_resourcesManager->LoadMesh("playerShip", &m_ship->m_model[0]);
	m_resourcesManager->LoadTexture("playerShip", &m_ship->m_model[0].m_meshTexturePoint);
	m_resourcesManager->LoadMesh("playerOars", &m_ship->m_model[1]);
	m_resourcesManager->LoadTexture("playerOars", &m_ship->m_model[1].m_meshTexturePoint);
	// バウンディングボックスを初期化
	m_ship->m_boundingBox->InitBox(4, 7, 8, 0.1f);

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
	RELEASE_CLASS_POINT(m_directionLight);		// ライト
	RELEASE_CLASS_POINT(m_shader);	// ベーシックシェーダー
	RELEASE_CLASS_POINT(m_celShader);	// トゥ―ンシェーダー
	RELEASE_CLASS_POINT(m_skyBox);	// トゥ―ンシェーダー

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
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);				// 光を使う
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			// 裏面をカリング
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	//pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		// αブレンドを行う
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
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
	{
		// テクニックを設定
		m_shader->m_shaderHandle = m_shader->m_effectPoint->GetTechniqueByName("RenderWithTextrue");
		m_shader->m_effectPoint->SetTechnique(m_shader->m_shaderHandle);

		// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
		m_skyBox->SetWorldMatrix();
		m_shader->m_effectPoint->SetMatrix(m_shader->m_WMatrixHandle, &m_skyBox->m_worldMatrix);
		D3DXMATRIX skyBoxVPmatrix = m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
		m_shader->m_effectPoint->SetMatrix(m_shader->m_VPMatrixHandle, &skyBoxVPmatrix);

		// テクスチャの設定
		m_shader->m_effectPoint->SetTexture(m_shader->m_textureHandle, m_skyBox->m_texture);

		// 描画
		UINT passNum = 0;
		m_shader->m_effectPoint->Begin(&passNum, 0);
		// 各パスを実行する
		for (int count = 0; count < passNum; count++)
		{
			m_shader->m_effectPoint->BeginPass(0);
			m_skyBox->Draw();

			m_shader->m_effectPoint->EndPass();
		}
		m_shader->m_effectPoint->End();
	}

	// オブジェクト種類番号
	int ship = 0, enemy = 1, cannon = 2;

	// ship
	{
		// テクニックを設定
		m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);

		// 変更行列を渡す
		m_ship->SetWorldMatrix();
		m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WMatrixHandle, &m_ship->m_worldMatrix);
		D3DXMATRIX shipVPmatrix = m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
		m_celShader->m_effectPoint->SetMatrix(m_celShader->m_VPMatrixHandle, &shipVPmatrix);	

		// Obj種類番号を渡す
		m_celShader->m_effectPoint->SetInt(m_celShader->m_typeHandle, ship);
		
		// マテリアル情報を渡す ... 臨時値
		D3DXCOLOR colorMtrlDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		D3DXCOLOR colorMtrlAmbient(0.35f, 0.35f, 0.35f, 0.0f);
		m_celShader->m_effectPoint->SetValue("materialAmbientColor", &colorMtrlAmbient, sizeof(D3DXCOLOR));
		m_celShader->m_effectPoint->SetValue("materialDiffuseColor", &colorMtrlDiffuse, sizeof(D3DXCOLOR));

		// テクスチャを渡す
		m_celShader->m_effectPoint->SetTexture("Tex", m_ship->m_model->m_meshTexturePoint);

		UINT passNum = 0;
		m_celShader->m_effectPoint->Begin(&passNum, 0);
		for (int count = 0; count < passNum; count++)
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

			UINT passNum = 0;
			m_shader->m_effectPoint->Begin(&passNum, 0);
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
		//for (int count1 = 0; count1 < ENEMY_MAX; count1++)
		//{
		//	if (m_enemyShip[count1].m_isLife == true)
		//	{
		//		m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定

		//		m_enemyShip[count1].SetWorldMatrix();
		//		m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WMatrixHandle, &m_enemyShip[count1].m_worldMatrix);
		//		D3DXMATRIX enemyVPmatrix = m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
		//		m_celShader->m_effectPoint->SetMatrix(m_celShader->m_VPMatrixHandle, &enemyVPmatrix);

		//		bool isShip = true;
		//		m_celShader->m_effectPoint->SetInt(m_celShader->m_typeHandle, enemy);

		//		UINT passNum = 0;	// パスの数
		//		m_celShader->m_effectPoint->Begin(&passNum, 0);
		//		for (int count = 0; count < passNum; count++)	// 各パスによって描画する
		//		{
		//			m_celShader->m_effectPoint->BeginPass(count);

		//			m_enemyShip[count1].Draw(m_celShader);

		//			m_celShader->m_effectPoint->EndPass();
		//		}
		//		m_celShader->m_effectPoint->End();
		//	}
		//}
	}

	// 弾
	{
	//	for (int count1 = 0; count1 < BULLET_MAX; count1++)
	//	{
	//		if (m_bullet[count1].m_isUse == true)
	//		{
	//			m_celShader->m_effectPoint->SetTechnique(m_celShader->m_celShaderHandle);	// テクニックを設定

	//			m_bullet[count1].SetWorldMatrix();
	//			m_celShader->m_effectPoint->SetMatrix(m_celShader->m_WMatrixHandle, &m_bullet[count1].m_worldMatrix);
	//			D3DXMATRIX bulletVPmatrix = m_camera->m_viewMatrix * m_camera->m_projectionMatrix;
	//			m_celShader->m_effectPoint->SetMatrix(m_celShader->m_VPMatrixHandle, &bulletVPmatrix);

	//			bool isShip = false;
	//			m_celShader->m_effectPoint->SetInt(m_celShader->m_typeHandle, cannon);

	//			UINT passNum = 0;	// パスの数
	//			m_celShader->m_effectPoint->Begin(&passNum, 0);
	//			for (int count = 0; count < passNum; count++)	// 各パスによって描画する
	//			{
	//				m_celShader->m_effectPoint->BeginPass(count);

	//				m_bullet[count1].Draw(m_celShader);

	//				m_celShader->m_effectPoint->EndPass();
	//			}
	//			m_celShader->m_effectPoint->End();
	//		}
	//	}
	}
		
	// デッバグメッセージ
	m_ship->PosToMessageAndMessageDraw(0);
	m_camera->PosToMessageAndMessageDraw(3);


}


//*****************************************************************************
//
// 操作関数
//
//*****************************************************************************
void Scene00::Control()
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
		
	if (GetKeyboardPress(DIK_I))	// カメラを上に移動
	{
		m_camera->MoveAlongVecLook(-0.5f);
	}
	else if (GetKeyboardPress(DIK_K))	// カメラを下に移動
	{
		m_camera->MoveAlongVecLook(0.5f);
	}

	if (GetKeyboardPress(DIK_O))	// カメラを上に移動
	{
		m_camera->ChangeRadius(true);
	}
	else if (GetKeyboardPress(DIK_P))	// カメラを下に移動
	{
		m_camera->ChangeRadius(false);
	}

	if (GetKeyboardTrigger(DIK_R))
	{
		m_camera->m_isShooting = !m_camera->m_isShooting;
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
		int i = 0;
		for (int count = 0; count < BULLET_MAX; count++)
		{
			if (m_bullet[count].m_isUse == false)
			{
				// プレーヤーによって弾を初期化,1回は3発で
				switch (i)
				{
				case 0:
					m_bullet[count].InitBulletByCharacter(m_ship->m_pos, -1 * m_ship->m_rightVector, true);
					i++;
					break;
				case 1:
					m_bullet[count].InitBulletByCharacter(m_ship->m_pos + m_ship->m_lookVector * 10.0f, -1 * m_ship->m_rightVector, true);
					i++;
					break;
				case 2:
					m_bullet[count].InitBulletByCharacter(m_ship->m_pos - m_ship->m_lookVector * 10.0f, -1 * m_ship->m_rightVector, true);
					i++;
					break;
				}
			}

			if (i == 3)
				break;
		}
	}

	// バウンディングボックス操作更新
	if (GetKeyboardTrigger(DIK_3))	// バウンディングボックスをコントロール
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