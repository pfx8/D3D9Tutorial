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
#include "Modules\Camera.h"

#define FIRST_UP_SPEED	10.0f
#define MOVE_SPEED		0.57f
#define ACCELERARION	-0.2f

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Bullet : public Character
{
private:
	float	speed;	// 最初のスピード

public:
	bool	isUse;		// 使われてるかどうかを判断する
	bool	isEnemyBullet;
	Model*	model;		// モデル

	Bullet();
	~Bullet();

	void InitBulletByCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 moveVector, bool isShip);	// エネミー座標を設定
	void BulletMove(D3DXVECTOR2 planeSize);	// エネミー移動
	void CheckBulletAndShip();	// エネミー攻撃

	void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);
};
#endif // !_BULLET_H_

