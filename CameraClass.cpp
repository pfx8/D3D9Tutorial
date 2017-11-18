//*****************************************************************************
//
// カメラクラス [CameraClass.cpp]
//
// Author : LIAO HANCHEN
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
	m_Message = new OutputMessage();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Camera::~Camera()
{
	SAFE_RELEASE_CLASS_POINT(m_Message);
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
	D3DXMatrixPerspectiveFovLH(&matProj,									// D3DXMatrixPerspectiveFovLHとD3DXMatrixPerspectiveLH？
							D3DXToRadian(45.0f),							// ビュー平面の視野角
							((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// ビュー平面のアスペクト比
							10.0f,											// ビュー平面のNearZ値
							1000.0f);										// ビュー平面のFarZ値

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
// カメラ位置を操作する
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

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Camera::PosToMessageAndMessageDraw(int row)
{
	m_Message->DrawPosMessage("CameraEye", m_posCameraEye, D3DXVECTOR2(0, float(row * 18 * 2)));
	m_Message->DrawPosMessage("CameraAt", m_posCameraAt, D3DXVECTOR2(0, float((row+1) * 18 * 2)));
}