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

#define FIRST_SPEED 7.0f
#define ACCELERARION	-0.05f
#define ONE_FRAME_TIME (1.0f / 60.0f)
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

	Bullet();
	~Bullet();

	void InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector);	// エネミー座標を設定
	void BulletMove();	// エネミー移動
	void CheckBulletAndShip();	// エネミー攻撃
};
#endif // !_BULLET_H_

