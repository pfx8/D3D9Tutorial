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
	m_upSpeed = FIRST_SPEED;

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
void Bullet::InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector)
{
	m_isUse = true;	// 使えるようになる
	
	// 位置を設定
	m_pos = pos;
	m_pos.y = 3.5f;
	m_lookVector = moveVector;	// 行き方向を設定

	m_boundingBox->InitBox(3, 13, 3, 0.1f);	// バウンディングボックスを初期化
}

//*****************************************************************************
//
// エネミー移動
//
//*****************************************************************************
void Bullet::BulletMove()
{
	m_pos -= m_lookVector * 0.1f;	// 行き方向へ移動
	
	// 垂直位置の計算 
	m_upSpeed += ACCELERARION;
	m_pos.y += 0.5f * (m_upSpeed)* ONE_FRAME_TIME;

	// 地図の範囲を超えたら、弾を消す
	if (m_pos.x >= 90.0f || m_pos.x <= -90.0f || m_pos.z >= 90.0f || m_pos.z <= -90.0f || m_pos.y <= 0.0f)
	{
		// 消したら数値を全部初期化
		m_isUse = false;
		m_upSpeed = FIRST_SPEED;
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