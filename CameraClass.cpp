//*****************************************************************************
//
// カメラクラス [CameraClass.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "CameraClass.h"
#include "Main.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Camera::Camera()
{

}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Camera::~Camera()
{

}

//*****************************************************************************
//
// カメラを初期化する
//
//*****************************************************************************
void Camera::InitCamera(D3DXVECTOR3 Eye, D3DXVECTOR3 At, D3DXVECTOR3 Up)
{
	// カメラの視点を初期化する
	m_posCameraEye = Eye;

	// カメラの注視点を初期化する
	m_posCameraAt = At;

	// カメラの上方向ベクトル、一般には (0, 1, 0) を定義する 
	m_vecCameraUP = Up;
}

//*****************************************************************************
//
// ビューイング変換
//
//*****************************************************************************
void Camera::setViewMatrix()
{
	D3DXMATRIX matView;

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&matView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&matView, &m_posCameraEye, &m_posCameraAt, &m_vecCameraUP);

	// ビューマトリックスの設定
	GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}

//*****************************************************************************
//
// プロジェクション変換(投影変換)
//
//*****************************************************************************
void Camera::setProjMatrix()
{
	D3DXMATRIX matProj;

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&matProj);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveLH(&matProj, D3DX_PI / 4.0f, 1.0f, 1.0f, 1000.0f);

	// プロジェクションマトリックスの設定
	GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
}

//*****************************************************************************
//
// ビューポートを設定
//
//*****************************************************************************
void Camera::setViewport()
{
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;

	// GetViewport
	GetDevice()->SetViewport(&vp);
}

//*****************************************************************************
//
// 視点操作
//
//*****************************************************************************
void Camera::Eye(float move, char direction)
{
	switch (direction)
	{
	case 'x':
	case 'X':m_posCameraEye.x += move; break; // zと同じ？
	case 'y':
	case 'Y':m_posCameraEye.y += move; break;
	case 'z':
	case 'Z':m_posCameraEye.z += move; break;
	default:
		break;
	}
}

//*****************************************************************************
//
// 注視点操作
//
//*****************************************************************************
void Camera::At(float move, char direction)
{
	switch (direction)
	{
	case 'x':
	case 'X':m_posCameraAt.x += move; break;
	case 'y':
	case 'Y':m_posCameraAt.y += move; break;
	case 'z':
	case 'Z':m_posCameraAt.z += move; break;
	default:
		break;
	}
}