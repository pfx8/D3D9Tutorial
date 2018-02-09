//*****************************************************************************
//
// エネミー処理 [Enemy.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <map>

#include "Engine.h"
#include "Bullet.h"
#include "DebugMessage.h"
#include "Modules\Character.h"
#include "Modules\BoundingBox.h"
#include "Modules\Model.h"
#include "Shader\CelShader.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Enemy : public Character
{
private:

public:
	bool	isLife;	// 生存フラグ
	float	time;		// タイムチェック
	bool	isAttack;	// 攻撃フラグ
	float	attackTime;	// 連続攻撃タイム

	Enemy();
	~Enemy();

	void InitEnemy(D3DXVECTOR3 pos);	// エネミー座標を設定
	void EnemyMove(D3DXVECTOR2 planeSize);	// エネミー移動
	bool EnemyAttack(Character* player);	// エネミー攻撃

	// 臨時
	void Trans(float angle);
	bool CheckBB(Character* player);
};
#endif // !_ENEMY_H_

