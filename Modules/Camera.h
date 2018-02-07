//*****************************************************************************
//
// カメラ処理 [Camera.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "Matrix.h"

#include "Character.h"
#include "../Engine.h"
#include "../DebugMessage.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Camera
{
private:
	DebugMessage*	m_message;

	float field, ratio, rangeStart, rangeEnd; // ビューイングの視野角、アスペクト比、NearZ値、FarZ値

public:
	D3DXVECTOR3		m_rot;			// カメラの回転角度
	// ベクトル
	D3DXVECTOR3		m_upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		m_lookVector;	// カメラの注視方向ベクトル
	D3DXVECTOR3		m_rightVector;	// カメラの右方向ベクトル
	// 位置
	D3DXVECTOR3		m_posEye;	// カメラの位置
	D3DXVECTOR3		m_posAt;		// カメラの注視点
	// マトリックス
	D3DXMATRIX		m_viewMatrix;		// ビューイング変換行列
	D3DXMATRIX		m_projectionMatrix;	// プロジェクション変換行列

	float			m_radius;			// カメラと船の半径
	bool			m_isShooting;

	Camera();
	~Camera();

	void InitCameraByPlayer(Character* player);	// カメラを初期化関数
	void SetViewport();	// ビューポートを設定
	void Update(Character* player);		// カメラ更新
	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する

	void RotationVecUp(float angle);		// 上方向のベクトルにして回転
	void RotationVecRight(float angle);	// 注視方向のベクトルにして回転
	void MoveAlongVecRight(float unit);	// 右方向に沿って移動
	void MoveAlongVecLook(float unit);	// 注視方向に沿って移動

	void isAtToEyeVectorMoreLong(bool isMoreLong);	// プレーヤーとカメラの半径を変わる

	void UpdateAngle(float angle);
	void ChangeRadius(bool isPlus);
};
#endif // !_CAMERA_H_