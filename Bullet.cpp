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
	m_upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_isUse = false;
	m_upSpeed = FIRST_UP_SPEED;

	// クラスポインタ
	m_model = new Model;
	m_message = new DebugMessage;
	m_boundingBox = new BoundingBox;

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Bullet::~Bullet()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(m_model);
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);
}

//*****************************************************************************
//
// プレーヤーによってエネミーの座標を設定
//
//*****************************************************************************
void Bullet::InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip)
{
	m_isUse = true;	// 使えるようになる

	if(isShip == true)
		m_isEnemyBullet = false;
	else
		m_isEnemyBullet = true;

	// 位置を設定
	m_pos = pos;
	m_pos.y = 1.5f + rand()%3;
	m_lookVector = moveVector * ((rand()%60 + 40) / 100.0f * 2.2f);	// 行き方向を設定

	m_boundingBox->InitBox(2, 3, 2, 0.1f);	// バウンディングボックスを初期化
}

//*****************************************************************************
//
// エネミー移動
//
//*****************************************************************************
void Bullet::BulletMove(D3DXVECTOR2 planeSize)
{
	m_pos -= m_lookVector * MOVE_SPEED;	// 行き方向へ移動
	
	// 垂直位置の計算 
	m_upSpeed += ACCELERARION;
	m_pos.y += 0.5f * (m_upSpeed)* ONE_FRAME_TIME;

	// 地図の範囲を超えたら、弾を消す
	if (/*m_pos.x >= planeSize.x || m_pos.x <= -planeSize.x || m_pos.z >= planeSize.y || m_pos.z <= -planeSize.y ||*/ m_pos.y <= 0.0f)
	{
		// 消したら数値を全部初期化
		m_isUse = false;
		m_upSpeed = FIRST_UP_SPEED;
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
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