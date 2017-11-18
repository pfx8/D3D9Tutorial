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

#include "MessageClass.h"
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
	D3DXVECTOR3		m_posCameraEye;			// カメラの位置
	D3DXVECTOR3		m_posCameraAt;			// カメラの注視点
	D3DXVECTOR3		m_vecCameraUP;			// カメラの上方向ベクトル

	OutputMessage*	m_Message;
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

	// カメラ位置を操作する
	void Eye(float move, char direction);

	// 座標をメッセージに渡して、画面に描画する
	void PosToMessageAndMessageDraw(int row);
};


#endif // !_CAMERA_CLASS_H_