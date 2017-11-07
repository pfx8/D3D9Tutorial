//*****************************************************************************
//
// カメラクラス [CameraClass.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************

#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "Main.h"

//*****************************************************************************
//
// マクロ定義
//
//*****************************************************************************


//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
class Camera
{
private:
	D3DXVECTOR3		m_posCameraEye;			// カメラの視点
	D3DXVECTOR3		m_posCameraAt;			// カメラの注視点
	D3DXVECTOR3		m_vecCameraUP;			// カメラの上方向ベクトル

public:
	Camera();
	~Camera();

	// カメラを初期化関数
	void InitCamera(D3DXVECTOR3 Eye, D3DXVECTOR3 At, D3DXVECTOR3 Up);

	// ビューイング変換
	void setViewMatrix();

	// プロジェクション変換(投影変換)
	void setProjMatrix();

	// ビューポートを設定
	void setViewport();

public: // 操作
	
	// 注視点
	void At(float move, char direction);

	// 視点
	void Eye(float move, char direction);
};


#endif // !_CAMERA_CLASS_H_