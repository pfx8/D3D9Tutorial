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

#define MAX_BACK_COEFFICIENT	(-0.38f)
#define MAX_FRONT_COEFFICIENT	(1.0f)

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
	UINT			m_leverLevel;		// 船のレバー操作
	int				m_modelNum;			// モデル数

public:
	double			m_speedCoefficient; // スピードに関する倍数
	DebugMessage*	m_message;		// Debugメッセージ
	float			m_waveAngle;	// 揺れ係数
	D3DXMATRIX		m_worldMatrix;	// ワールド変換マトリックス
	D3DXMATRIX		m_rotMatrix;	// 回転マトリックス

	// ベクトル
	D3DXVECTOR3		m_upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		m_lookVector;	// カメラの注視方向ベクトル
	D3DXVECTOR3		m_rightVector;	// カメラの右方向ベクトル

	// 固定属性
	D3DXVECTOR3		m_pos;			// 位置
	D3DXVECTOR3		m_rot;			// 回転
	D3DXVECTOR3		m_scl;			// 拡大縮小
	Model*			m_model;		// メッシュ
	BoundingBox*	m_boundingBox;	// バウンディングボックス

	Character();
	~Character();

	void InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction, int modelNum);		// 座標を設定

	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する
	void SetWorldMatrix();						// ワールド変換を設定
	void Draw(CelShader* celShader);			// キャラクターの描画(Shader)
	
	void Update(float rot);				// キャラクター更新
	bool CheckHitBB(Character* Object);	// 当たり判定

	void RotationVecUp(float angle);			// 上方向のベクトルにして回転
	D3DXVECTOR3  MoveAlongVecLook(float unit);	// 注視方向に沿って移動

	void ChangeLever(LEVER_LEVEL scalars);		// レバーの操作によってスピードを変わる
	D3DXMATRIX GetRotMatrix();					// 回転マトリックスを取得
};
#endif // !_CHARACTER_H_

