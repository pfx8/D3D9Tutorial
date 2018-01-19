//*****************************************************************************
//
// 弾処理 [Bullet.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _BULLET_H_
#define _BULLET_H_

#include <map>

#include "Engine.h"
#include "Modules\Character.h"

#define FIRST_UP_SPEED	10.0f
#define MOVE_SPEED		1.0f
#define ACCELERARION		-0.2f
#define ONE_FRAME_TIME	(1.0f / 60.0f)
//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Bullet : public Character
{
private:
	float m_upSpeed;	// 最初のスピード

public:
	bool m_isUse;	// 使われてるかどうかを判断する
	bool m_isEnemyBullet;

	Bullet();
	~Bullet();

	void InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip);	// エネミー座標を設定
	void BulletMove(D3DXVECTOR2 planeSize);	// エネミー移動
	void CheckBulletAndShip();	// エネミー攻撃
};
#endif // !_BULLET_H_

