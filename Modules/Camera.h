//*****************************************************************************
//
// カメラ処理 [Camera.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "../Engine.h"
#include "../DebugMessage.h"

#include "Matrix.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Camera
{
private:
	// ベクトル
	D3DXVECTOR3		m_upVector;		// カメラの上方向ベクトル
	D3DXVECTOR3		m_lookVector;	// カメラの注視方向ベクトル
	D3DXVECTOR3		m_rightVector;	// カメラの右方向ベクトル
	// 回転角度
	D3DXVECTOR3		m_rot;			// カメラの回転角度
	DebugMessage*	m_message;

public:
	// 位置
	D3DXVECTOR3	m_posEye;	// カメラの位置
	D3DXVECTOR3	m_posAt;		// カメラの注視点
	D3DXVECTOR3	m_atToEyeVector;	// カメラから注視点までのベクトル
	// マトリックス
	D3DXMATRIX	m_viewMatrix;		// ビューイング変換行列
	D3DXMATRIX	m_projectionMatrix;	// プロジェクション変換行列

	Camera();
	~Camera();

	void InitCamera(D3DXVECTOR3 Eye, D3DXVECTOR3 At, D3DXVECTOR3 Up);	// カメラを初期化関数
	void SetViewMatrix();	// ビューイング変換
	void SetProjMatrix();	// プロジェクション変換(投影変換)
	void SetViewport();	// ビューポートを設定
	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する

	void RotationVecUp(float angle);		// 上方向のベクトルにして回転
	void RotationVecRight(float angle);	// 注視方向のベクトルにして回転
	void MoveAlongVecRight(float unit);	// 右方向に沿って移動
	void MoveAlongVecLook(float unit);	// 注視方向に沿って移動

	void isAtToEyeVectorMoreLong(bool isMoreLong);	// プレーヤーとカメラの半径を変わる

public: 
	void Update(D3DXVECTOR3* playerDirectionVector);	// カメラ更新
	void UpdateAt(D3DXVECTOR3 pos);	// 注視点座標を更新
};
#endif // !_CAMERA_H_