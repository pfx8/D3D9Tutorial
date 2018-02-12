//*****************************************************************************
//
// エネミー処理 [Enemy.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Enemy.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Enemy::Enemy()
{
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//this->directionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->waveAngle = 0.0f;
	this->isLife = true;
	this->time = 0.016 * 120;
	this->isAttack = false;
	this->attackTime = 0.016 * 180;

	// クラスポインタ
	this->message = new DebugMessage;
	this->boundingBox = new BoundingBox;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Enemy::~Enemy()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(this->message);
	RELEASE_CLASS_POINT(this->boundingBox);
}

//*****************************************************************************
//
// エネミー座標を設定
//
//*****************************************************************************
void Enemy::InitEnemy(D3DXVECTOR3 pos)
{
	this->pos = pos;	// 位置
	this->boundingBox->InitBox(5, 11, 10, 0.1f);	// バウンディングボックスを初期化
}

//*****************************************************************************
//
// エネミー移動
//
//*****************************************************************************
void Enemy::EnemyMove(D3DXVECTOR2 planeSize)
{
	// 地図の範囲を超えたら、逆方向に行く
	if (this->pos.x >= planeSize.x * 0.8f || this->pos.x <= -planeSize.x * 0.8f || this->pos.z >= planeSize.y * 0.8f || this->pos.z <= -planeSize.y * 0.8f)
	{
		if (this->time == 0.016f * 120)
		{
			//RotationVecUp(D3DX_PI);
			Trans(D3DX_PI);
		}
	}

	this->time -= 0.016f;
	if (this->time <= 0.0f)
	{
		this->time = 0.016f * 120;
	}

	if (this->isAttack == true)
	{
		this->attackTime -= 0.016f;
		if (this->attackTime <= 0.0f)
		{
			this->isAttack = false;
			this->attackTime = 0.016f * 120;
		}
	}

	this->pos -= this->lookVector * 0.1f;	// 行き方向へ移動
}

//*****************************************************************************
//
// エネミー攻撃
//
//*****************************************************************************
bool Enemy::EnemyAttack(Character* player)
{
	if (CheckBB(player) == true)
	{
		return true;
	}

	return false;
}

//*****************************************************************************
//
// プレーヤーを発見するかどうかの判定
//
//*****************************************************************************
bool Enemy::CheckBB(Character* player)
{
	// 弾
	D3DXVECTOR3 playerPos = player->pos;
	D3DXVECTOR3 playerBoxSize = player->boundingBox->size;
	// エネミー
	D3DXVECTOR3 enemyPos = this->pos;
	D3DXVECTOR3 enemyBoxSize;
	enemyBoxSize.x = this->lookVector.x * 100;
	enemyBoxSize.y = 10;
	enemyBoxSize.z = this->lookVector.z * 100;

	if (
		/*playerPos.x + playerBoxSize.x / 2 > enemyPos.x - enemyBoxSize.x / 2 &&
		playerPos.x - playerBoxSize.x / 2 < enemyPos.x + enemyBoxSize.x / 2 &&
		playerPos.y - playerBoxSize.y / 2 < enemyPos.y + enemyBoxSize.y / 2 &&
		playerPos.y + playerBoxSize.y / 2 > enemyPos.y - enemyBoxSize.y / 2 &&
		playerPos.z + playerBoxSize.z / 2 > enemyPos.z - enemyBoxSize.z / 2 &&
		playerPos.z - playerBoxSize.z / 2 < enemyPos.z + enemyBoxSize.z / 2*/
		playerPos.x + playerBoxSize.x / 2 > enemyPos.x - enemyBoxSize.x / 2 &&
		playerPos.x - playerBoxSize.x / 2 < enemyPos.x &&
		playerPos.y - playerBoxSize.y / 2 < enemyPos.y &&
		playerPos.y + playerBoxSize.y / 2 > enemyPos.y - enemyBoxSize.y / 2 &&
		playerPos.z + playerBoxSize.z / 2 > enemyPos.z - enemyBoxSize.z / 2 &&
		playerPos.z - playerBoxSize.z / 2 < enemyPos.z
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
// 
//
//*****************************************************************************
void Enemy::Trans(float angle)
{
	if (this->rot.y > D3DX_PI * 2.0f || this->rot.y < -D3DX_PI * 2.0f)
	{
		this->rot.y = 0;
	}

	// 角度を記録する
	this->rot.y -= angle;

	// 新しい右方向ベクトルを計算する
	//this->rightVector.x = cosf(this->rot.y);
	//this->rightVector.z = sinf(this->rot.y);

	// 新しい注視方向ベクトルを計算する
	//this->lookVector.x = cosf(this->rot.y + D3DX_PI / 2);
	//this->lookVector.z = sinf(this->rot.y + D3DX_PI / 2);
	
	this->lookVector.x = cosf(-this->rot.y + D3DX_PI / 2);
	this->lookVector.z = sinf(-this->rot.y + D3DX_PI / 2);
}