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
	DebugMessage*	message;
	D3DXVECTOR3		offSetFromPlayer;				// プレーヤーとカメラの偏り(半径)

	float offsetFromTargetMin;						// プレーヤーとカメラの偏りの最小値
	float offsetFromTargetMax;						// プレーヤーとカメラの偏りの最大値
	float verticalRadiansMin;						// カメラの垂直角度の最小値
	float verticalRadiansMax;						// カメラの垂直角度の最大値

	float field;									// ビューイングの視野角
	float ratio;									// アスペクト比
	float rangeStart;								// NearZ値
	float rangeEnd;									// FarZ値


public:
	float rotateSpeedHorizonal;						// カメラの水平移動偏り量
	float rotateSpeedVertical;						// カメラの垂直移動偏り量
	float zoomSpeed;								// ゾーンの移動偏り量

	D3DXVECTOR3		upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		lookVector;	// カメラの注視方向ベクトル
	D3DXVECTOR3		rightVector;	// カメラの右方向ベクトル

	D3DXVECTOR3		posEye;	// カメラの位置
	D3DXVECTOR3		posAt;	// カメラの注視点

	D3DXMATRIX		viewMatrix;		// ビューイング変換行列
	D3DXMATRIX		projectionMatrix;	// プロジェクション変換行列

	//bool			m_isShooting;

	void Update(Character* player);														// カメラ更新
	void Rotation(Character* player, float radiansHorizonal, float radiansVertical);	// 回転操作
	void Zoom(float distance);															// ズーム操作

	Camera();
	~Camera();

	void InitCameraByPlayer(Character* player);	// カメラを初期化関数
	void SetViewport();	// ビューポートを設定

	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する

	//void RotationVecUp(float angle);		// 上方向のベクトルにして回転
	//void RotationVecRight(float angle);	// 注視方向のベクトルにして回転
};
#endif // !_CAMERA_H_