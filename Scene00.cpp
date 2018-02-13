//*****************************************************************************
//
// D3DTutorial処理 [Scene00.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene00.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene00::Scene00()
{
	// BasicShader
	this->shader = new Shader;

	// CelShader
	this->celShader = new CelShader;

	// ShadowMapShader
	//this->shadowMap = new ShadowMapShader;

	// RHWポリゴン
	this->screenPolygon = new ScreenPolygon;

	// ライト、光方向はデフォルトで
	this->directionLight = new Light;

	// スカイボックス
	this->skyBox = new SkyBox;

	// フィールド
	this->sea = new Plane;
	
	// 主人公
	this->ship = new Character;

	// シャドー
	this->shadowMap = new ShadowMapShader;

	// 敵
	this->enemyShip = new Enemy[ENEMY_MAX];

	// 弾
	this->bullet = new Bullet[BULLET_MAX];

	// カメラ
	this->camera = new Camera;

	// 初期化
	InitScene00();
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Scene00::InitScene00()
{
	// BasicShader
	this->shader->InitShader();

	// CelShader
	this->celShader->InitShader();

	// ShadowMapShader
	//this->shadowMap->InitShader();

	// ライト、光方向はデフォルトで
	this->celShader->effectPoint->SetValue("lightDir", &this->directionLight->light.Direction, sizeof(D3DXVECTOR3));
	this->celShader->effectPoint->SetValue("lightDiffuse", &this->directionLight->light.Diffuse, sizeof(D3DXCOLOR));
	this->celShader->effectPoint->SetValue("lightSpecular", &this->directionLight->light.Specular, sizeof(D3DXCOLOR));

	// スカイボックス
	this->skyBox->InitSkyBox(2500.0f);
	this->resourcesManager->LoadTexture("skybox", &this->skyBox->texture);
	/*this->resourcesManager->LoadTexture("front", &this->skyBox->texture[0]);
	this->resourcesManager->LoadTexture("back", &this->skyBox->texture[1]);
	this->resourcesManager->LoadTexture("left", &this->skyBox->texture[2]);
	this->resourcesManager->LoadTexture("right", &this->skyBox->texture[3]);
	this->resourcesManager->LoadTexture("top", &this->skyBox->texture[4]);*/

	// フィールド
	this->sea->InitPlane(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(17.0f, 17.0f), D3DXVECTOR2(150, 150));
	this->resourcesManager->LoadTexture("fieldSea2", &this->sea->texture);

	// 主人公
	this->ship->InitCharacter();
	this->resourcesManager->LoadMesh("shipBody", this->ship->player.shipBody);
	this->resourcesManager->LoadTexture("shipBody", &this->ship->player.shipBody->meshTexturePoint);
	this->resourcesManager->LoadMesh("shipCannon", this->ship->player.shipCannon);
	this->resourcesManager->LoadTexture("shipCannon", &this->ship->player.shipCannon->meshTexturePoint);
	// バウンディングボックスを初期化
	/*this->ship->boundingBox->InitBox(4, 7, 8, 0.1f);*/
	this->ship->check->InitBox(20, 20, 20, 0.1f);
	this->ship->space->InitBox(30, 30, 30, 0.1f);

	// シャドー
	this->shadowMap->InitShader();

	// 敵
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
		this->enemyShip[count].InitEnemy(temp);
		this->resourcesManager->LoadMesh("shipBody", this->enemyShip[count].player.shipBody);
		this->resourcesManager->LoadTexture("shipBody", &this->enemyShip[count].player.shipBody->meshTexturePoint);
		this->resourcesManager->LoadMesh("shipCannon", this->enemyShip[count].player.shipCannon);
		this->resourcesManager->LoadTexture("shipCannon", &this->enemyShip[count].player.shipCannon->meshTexturePoint);
		this->enemyShip[count].check->InitBox(4, 7, 8, 0.1f);	// バウンディングボックスを初期化
		this->enemyShip[count].Trans((rand() % 80) / 180.0f * D3DX_PI);		// 向きを決める
	}

	// 弾
	for (int count = 0; count < BULLET_MAX; count++)
	{
		this->resourcesManager->LoadMesh("ball", this->bullet[count].model);
	}

	// カメラ
	this->camera->InitCameraByPlayer(this->ship);

	std::cout << "[State] BoundingBox: " << std::boolalpha << this->ship->check->isBoundingBoxDraw << std::endl;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene00::~Scene00()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(this->sea);	// フィールド
	RELEASE_CLASS_POINT(this->ship);		// プレーヤー
	RELEASE_CLASS_POINT(this->camera);	// カメラ
	RELEASE_CLASS_POINT(this->directionLight);		// ライト
	RELEASE_CLASS_POINT(this->shader);	// ベーシックシェーダー
	RELEASE_CLASS_POINT(this->celShader);	// トゥ―ンシェーダー
	RELEASE_CLASS_POINT(this->skyBox);	// トゥ―ンシェーダー

	RELEASE_CLASS_ARRY_POINT(this->enemyShip); // エネミー
	RELEASE_CLASS_ARRY_POINT(this->bullet); // エネミー
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
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);					// Zバッファを使用
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
}

//*****************************************************************************
//
// シンーの更新
//
//*****************************************************************************
void Scene00::Update()
{
	// 入力操作
	Control();

	// カメラ更新
	this->camera->Update(this->ship);

	// 波の更新
	this->sea->Update();	

	// 弾移動更新
	for (int count = 0; count < BULLET_MAX; count++)
	{
		if (this->bullet[count].isUse == true)
		{
			this->bullet[count].BulletMove(D3DXVECTOR2(200.0f, 200.0f));
		}
	}

	// 敵移動更新
	for (int count = 0; count < ENEMY_MAX; count++)
	{
		if (this->enemyShip[count].isLife == true)
		{
			this->enemyShip[count].EnemyMove(D3DXVECTOR2(150.0f, 150.0f));
		}
	}

	// 敵の攻撃
	for (int count = 0; count < ENEMY_MAX; count++)
	{
		if (this->enemyShip[count].EnemyAttack(this->ship) == true && this->enemyShip[count].isAttack == false)
		{
			for (int count2 = 0; count2 < BULLET_MAX; count2++)
			{
				if (this->bullet[count2].isUse == false)
				{
					this->bullet[count2].InitBulletByCharacter(this->enemyShip[count].pos, this->enemyShip[count].lookVector, false); // プレーヤーによって弾を初期化
					this->enemyShip[count].isAttack = true;
					break;
				}
			}
		}
	}

	// 弾と敵の当たり判定
	for (int count = 0; count < BULLET_MAX; count++)
	{
		if (this->bullet[count].isUse == true && this->bullet[count].isEnemyBullet == false)
		{
			for (int count2 = 0; count2 < ENEMY_MAX; count2++)
			{
				if (this->enemyShip[count2].isLife == true && this->enemyShip[count2].isAttack == false)
				{
					if (CheckBB((this->bullet + count), (this->enemyShip + count2)))
					{
						this->bullet[count].isUse = false;
						this->enemyShip[count2].isLife = false;
						this->enemyShip[count2].time = 0.016f * 120;
					}
				}
			}
		}
	}
	
	// 揺れる状況
	this->ship->Update(this->sea->waveAngle);
	for (int count = 0; count < ENEMY_MAX; count++)
	{
		this->enemyShip[count].Update(this->sea->waveAngle);
	}

	// UI更新
	this->screenPolygon->Update(this->ship, this->enemyShip);
}

//*****************************************************************************
//
// シンーの描画
//
//*****************************************************************************
void Scene00::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// VP行列を求める
	D3DXMATRIX VPmatrix = this->camera->viewMatrix * this->camera->projectionMatrix;

	// フォグ

	// フィールド
	{
		// テクニックを設定
		this->shader->shaderHandle = this->shader->effectPoint->GetTechniqueByName("RenderWithTextrue");
		this->shader->effectPoint->SetTechnique(this->shader->shaderHandle);
			
		// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
		this->shader->effectPoint->SetMatrix(this->shader->WMatrixHandle, &this->sea->worldMatrix);	
		D3DXMATRIX fieldVPmatrix = this->camera->viewMatrix * this->camera->projectionMatrix;
		this->shader->effectPoint->SetMatrix(this->shader->VPMatrixHandle, &fieldVPmatrix);
			
		// テクスチャ、アルファ値の設定
		this->shader->effectPoint->SetTexture(this->shader->textureHandle, this->sea->texture);
		this->shader->effectPoint->SetFloat(this->shader->alphaHandle, 1.0f);
			
		// 描画
		UINT passNum = 0;
		this->shader->effectPoint->Begin(&passNum, 0);
		// 各パスを実行する
		for (int count = 0; count < passNum; count++)
		{
			this->shader->effectPoint->BeginPass(0);
			this->sea->Draw();

			this->shader->effectPoint->EndPass();
		}
		this->shader->effectPoint->End();
	}

	// スカイボックス
	{
		// テクニックを設定
		this->shader->shaderHandle = this->shader->effectPoint->GetTechniqueByName("RenderWithTextrue");
		this->shader->effectPoint->SetTechnique(this->shader->shaderHandle);

		// ワールド変換、ビューイング変換、プロジェクション変換マトリックス
		this->skyBox->SetWorldMatrix();
		this->shader->effectPoint->SetMatrix(this->shader->WMatrixHandle, &this->skyBox->worldMatrix);
		D3DXMATRIX skyBoxVPmatrix = this->camera->viewMatrix * this->camera->projectionMatrix;
		this->shader->effectPoint->SetMatrix(this->shader->VPMatrixHandle, &skyBoxVPmatrix);

		// テクスチャの設定
		this->shader->effectPoint->SetTexture(this->shader->textureHandle, this->skyBox->texture);

		// 描画
		UINT passNum = 0;
		this->shader->effectPoint->Begin(&passNum, 0);
		// 各パスを実行する
		for (int count = 0; count < passNum; count++)
		{
			this->shader->effectPoint->BeginPass(0);
			this->skyBox->Draw();

			this->shader->effectPoint->EndPass();
		}
		this->shader->effectPoint->End();
	}

	// オブジェクト種類番号
	int ship = 0, enemy = 1, cannon = 2;

	// ship
	{
		// モデルを描画する
		this->ship->Draw(this->celShader, &VPmatrix);

		// バウンディングボックス
		this->ship->check->Draw(this->shader, &VPmatrix);
		this->ship->space->Draw(this->shader, &VPmatrix);	
	
		// シャドー
		//this->shadowMap->effectPoint->SetTechnique("");
	}

	// エネミー
	{
		/*for (int count1 = 0; count1 < ENEMY_MAX; count1++)
		{
			if (this->enemyShip[count1].isLife == true)
			{
				this->enemyShip[count1].Draw(this->celShader, &VPmatrix);
			}
		}*/
	}

	// 弾
	{
		for (int count1 = 0; count1 < BULLET_MAX; count1++)
		{
			if (this->bullet[count1].isUse == true)
			{
				D3DXMATRIX VPmatrix = this->camera->viewMatrix * this->camera->projectionMatrix;
				this->bullet[count1].Draw(this->celShader, &VPmatrix);
			}
		}
	}

	// ゲームUI
	this->screenPolygon->Draw();
		
	// デッバグメッセージ
	this->ship->PosToMessageAndMessageDraw(0);
	//this->camera->PosToMessageAndMessageDraw(0);


}


//*****************************************************************************
//
// 操作関数
//
//*****************************************************************************
void Scene00::Control()
{
	// プレーヤー攻撃(左)
	int  leftButton = 0;
	bool isLeftShooting;
	int  rightButton = 0;
	bool isRightShooting;

	/*if (this->ship->rot.y <= D3DXToRadian(90) && this->ship->rot.y >= -D3DXToRadian(90))
	{
		leftButton = DIK_N;
		isLeftShooting = this->ship->leftShooting;
		rightButton = DIK_M;
		isRightShooting = this->ship->rightShooting;
	}
	else
	{
		leftButton = DIK_M;
		isLeftShooting = this->ship->rightShooting;
		rightButton = DIK_N;
		isRightShooting = this->ship->leftShooting;
	}*/

	if (GetKeyboardTrigger(/*leftButton*/DIK_N) && (/*isLeftShooting*/this->ship->leftShooting == false))
	{
		int i = 0;
		D3DXVECTOR3 temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		temp = -this->ship->rightVector;

		for (int count = 0; count < BULLET_MAX; count++)
		{
			if (this->bullet[count].isUse == false)
			{
				// プレーヤーによって弾を初期化,1回は4発で
				switch (i)
				{
				case 0:
					this->bullet[count].InitBulletByCharacter(this->ship->pos + this->ship->lookVector * 6.0f, temp, true);
					i++;
					break;
				case 1:
					this->bullet[count].InitBulletByCharacter(this->ship->pos + this->ship->lookVector * 2.0f, temp, true);
					i++;
					break;
				case 2:
					this->bullet[count].InitBulletByCharacter(this->ship->pos - this->ship->lookVector * 2.0f, temp, true);
					i++;
					break;
				case 3:
					this->bullet[count].InitBulletByCharacter(this->ship->pos - this->ship->lookVector * 6.0f, temp, true);
					i++;
					break;
				}
			}

			if (i == 4)
				break;
		}

		this->ship->leftShooting = true;
	}

	if (GetKeyboardTrigger(/*rightButton*/DIK_M) && (/*isRightShooting*/this->ship->rightShooting == false))
	{
		int i = 0;
		D3DXVECTOR3 temp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		temp = this->ship->rightVector;

		for (int count = 0; count < BULLET_MAX; count++)
		{
			if (this->bullet[count].isUse == false)
			{
				// プレーヤーによって弾を初期化,1回は4発で
				switch (i)
				{
				case 0:
					this->bullet[count].InitBulletByCharacter(this->ship->pos + this->ship->lookVector * 6.0f, temp, true);
					i++;
					break;
				case 1:
					this->bullet[count].InitBulletByCharacter(this->ship->pos + this->ship->lookVector * 2.0f, temp, true);
					i++;
					break;
				case 2:
					this->bullet[count].InitBulletByCharacter(this->ship->pos - this->ship->lookVector * 2.0f, temp, true);
					i++;
					break;
				case 3:
					this->bullet[count].InitBulletByCharacter(this->ship->pos - this->ship->lookVector * 6.0f, temp, true);
					i++;
					break;
				}
			}

			if (i == 4)
				break;
		}

		this->ship->rightShooting = true;
	}

	// バウンディングボックス操作更新
	if (GetKeyboardTrigger(DIK_3))	// バウンディングボックスをコントロール
	{
		// プレーヤー
		this->ship->check->isBoundingBoxDraw = !this->ship->check->isBoundingBoxDraw;	// バウンディングボックスをコントロール
		this->ship->space->isBoundingBoxDraw = !this->ship->space->isBoundingBoxDraw;	// バウンディングボックスをコントロール

		// エネミー
		for (int count = 0; count < ENEMY_MAX; count++)
		{
			this->enemyShip[count].check->isBoundingBoxDraw = !this->enemyShip[count].check->isBoundingBoxDraw;
			this->enemyShip[count].space->isBoundingBoxDraw = !this->enemyShip[count].space->isBoundingBoxDraw;
		}
			
		// 弾
		for (int count = 0; count < BULLET_MAX; count++)
		{
			this->bullet[count].check->isBoundingBoxDraw = !this->bullet[count].check->isBoundingBoxDraw;
			this->bullet[count].space->isBoundingBoxDraw = !this->bullet[count].space->isBoundingBoxDraw;
		}

		std::cout << "[State] BoundingBox: " << std::boolalpha << this->ship->check->isBoundingBoxDraw << std::endl;
	}
}

//*****************************************************************************
//
// 当たり判定(長方形)
//
//*****************************************************************************
bool Scene00::CheckBB(Bullet* bullet, Enemy* enemy)
{
	// 弾
	D3DXVECTOR3 bulletPos = bullet->pos;
	D3DXVECTOR3 bulletBoxSize = bullet->check->size;
	// エネミー
	D3DXVECTOR3 enemyPos = enemy->pos;
	D3DXVECTOR3 enemyBoxSize = enemy->check->size;

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

//*****************************************************************************
//
// 当たり判定(円)
//
//*****************************************************************************
bool Scene00::CheckBC(Bullet* bullet, Enemy* enemy)
{
	D3DXVECTOR3 temp = bullet->pos - enemy->pos;
	float fTempLenghtSq = D3DXVec3LengthSq(&temp);

	float bulletR = bullet->check->radius;
	float enemyR = enemy->check->radius;

	if (fTempLenghtSq <= (bulletR + enemyR) * (bulletR + enemyR))
	{
		return true;
	}
	else
	{
		return false;
	}
}