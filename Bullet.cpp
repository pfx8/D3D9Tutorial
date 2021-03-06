//*****************************************************************************
//
// 弾処理 [Bullet.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Bullet.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Bullet::Bullet()
{
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->isUse = false;
	this->speed = 0.0f;

	// クラスポインタ
	this->model = new Model;
	this->message = new DebugMessage;
	this->check = new BoundingBox;

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Bullet::~Bullet()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(this->model);
	RELEASE_CLASS_POINT(this->message);
	RELEASE_CLASS_POINT(this->check);
}

//*****************************************************************************
//
// プレーヤーによってエネミーの座標を設定
//
//*****************************************************************************
void Bullet::InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip)
{
	this->isUse = true;	// 使えるようになる

	if(isShip == true)
		this->isEnemyBullet = false;
	else
		this->isEnemyBullet = true;

	// 位置を設定
	this->pos = pos + moveVector * 6.0f;
	this->pos.y = 4.0f;
	this->lookVector = moveVector * ((rand()%60 + 40) / 100.0f * 2.2f);	// 行き方向を設定
	this->speed = FIRST_UP_SPEED + rand()%11;

	this->check->InitBox(2, 2, 2, 0.1f);	// バウンディングボックスを初期化
}

//*****************************************************************************
//
// エネミー移動
//
//*****************************************************************************
void Bullet::BulletMove(D3DXVECTOR2 planeSize)
{
	this->pos += this->lookVector * MOVE_SPEED;	// 行き方向へ移動
	
	// 垂直位置の計算 
	this->speed += ACCELERARION;
	this->pos.y += 0.5f * (this->speed)* ONE_FRAME_TIME;

	// 地図の範囲を超えたら、弾を消す
	if ( this->pos.y <= 0.0f)
	{
		// 消したら数値を全部初期化
		this->isUse = false;
		this->speed = FIRST_UP_SPEED;
		this->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	}
}

//*****************************************************************************
//
// エネミー攻撃
//
//*****************************************************************************
void Bullet::CheckBulletAndShip()
{

}

//*****************************************************************************
//
// 描画
//
//*****************************************************************************
void Bullet::Draw(CelShader* celShader, D3DXMATRIX* VPMatrix)
{
	SetWorldMatrix();

	model->DrawModel(celShader, &this->worldMatrix, VPMatrix, &this->lightMatrix, &this->normalMatrix, MT_bullet);
}