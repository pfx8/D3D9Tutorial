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
	bool m_isLife;	// 生存フラグ

	Enemy();
	~Enemy();

	void InitEnemy(D3DXVECTOR3 pos);	// エネミー座標を設定
	void EnemyMove(D3DXVECTOR2 planeSize);	// エネミー移動
	void EnemyAttack();	// エネミー攻撃
};
#endif // !_ENEMY_H_

