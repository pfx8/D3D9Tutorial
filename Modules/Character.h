//*****************************************************************************
//
// キャラクターベース処理 [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <map>

#include "Model.h"
#include "BoundingBox.h"
#include "..\Engine.h"
#include "..\DebugMessage.h"
#include "..\Shader\CelShader.h"

// 移動　= lookVector * SPEED_COEFFICIENT
#define MAX_BACK_SPEED_COEFFICIENT	(-0.38f)
#define MAX_FRONT_SPEED_COEFFICIENT	(0.55f)

#define MAX_HP						(3)

#define BULLET_TIME					(3.0f)

struct PlayerModel
{
	Model*			shipBody;
	Model*			shipCannon;
};

typedef enum
{
	LL_BACK = -1,	// [-1]後退
	LL_STOP,		// [0]停止
	LL_FRONT,		// [1]前進
}LEVER_LEVEL;

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Character
{
private:

public:
	LEVER_LEVEL		leverLevel;		// 船のレバー操作
	double			speed;			// スピードに関する倍数
	DebugMessage*	message;		// Debugメッセージ
	float			waveAngle;		// 揺れ係数
	D3DXMATRIX		worldMatrix;	// ワールド変換マトリックス
	D3DXMATRIX		lightMatrix;	// ライトマトリックス

	// ベクトル
	D3DXVECTOR3		upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		lookVector;		// カメラの注視方向ベクトル
	D3DXVECTOR3		rightVector;	// カメラの右方向ベクトル

	// 固定属性
	D3DXVECTOR3		pos;			// 位置
	D3DXVECTOR3		rot;			// 回転
	D3DXVECTOR3		scl;			// 拡大縮小

	PlayerModel		player;			// プレーヤーモデル集合
	BoundingBox*	boundingBox;	// バウンディングボックス
	
	int				HP;

	float			leftTime;
	float			rightTime;

	Character();
	~Character();

	D3DXVECTOR3  MoveAlongVecLook(float speedCoefficient);	// 注視方向に沿って移動
	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する
	void SetWorldMatrix();						// ワールド変換を設定
	void Update(float rot);						// キャラクター更新
	void ChangeLever(LEVER_LEVEL level);		// レバーの操作によってスピードを変わる
	bool CheckHitBB(Character* Object);			// 当たり判定
	void RotationVecUp(float angle);			// 上方向のベクトルにして回転

	virtual void Draw(CelShader* celShader, D3DXMATRIX* VPMatrix);	// キャラクターの描画

	void InitCharacter();
};
#endif // !_CHARACTER_H_

