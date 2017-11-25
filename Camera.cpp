//*****************************************************************************
//
// カメラ処理 [Camera.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Camera.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Camera::Camera()
{
	m_posEye = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posAt  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecUP  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_DirectionVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//m_Message = new DebugMessage();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Camera::~Camera()
{
	//SAFE_RELEASE_CLASS_POINT(m_Message);
}

//*****************************************************************************
//
// カメラを初期化する
//
//*****************************************************************************
void Camera::InitCamera(D3DXVECTOR3 Eye, D3DXVECTOR3 At, D3DXVECTOR3 Up)
{
	// カメラの視点を初期化する
	m_posEye = Eye;

	// カメラの注視点を初期化する
	m_posAt = At;

	// カメラの上方向ベクトル、一般には (0, 1, 0) を定義する 
	m_vecUP = Up;

	// 方向ベクトルを初期化する
	m_DirectionVector = m_posEye - At;
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
	D3DXMatrixLookAtLH(&matView, &m_posEye, &m_posAt, &m_vecUP);

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
							1.0f,											// ビュー平面のNearZ値
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
	case 'X':m_posEye.x += move; break; // zと同じ？
	case 'y':
	case 'Y':m_posEye.y += move; break;
	case 'z':
	case 'Z':m_posEye.z += move; break;
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
	case 'X':m_posAt.x += move; break;
	case 'y':
	case 'Y':m_posAt.y += move; break;
	case 'z':
	case 'Z':m_posAt.z += move; break;
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
	//m_Message->DrawPosMessage("CameraEye", m_posEye, D3DXVECTOR2(0, float(row * 18 * 2)));
	//m_Message->DrawPosMessage("CameraAt", m_posAt, D3DXVECTOR2(0, float((row+1) * 18 * 2)));
}

//*****************************************************************************
//
// カメラ更新
//
//*****************************************************************************
void Camera::Update()
{
	if (GetKeyboardPress(DIK_J))			// key J
	{
		Eye(1.0f, 'x');
	}
	if (GetKeyboardPress(DIK_L))			// key L
	{
		Eye(-1.0f, 'x');
	}
	if (GetKeyboardPress(DIK_I))			// key I
	{
		Eye(1.0f, 'y');
	}
	if (GetKeyboardPress(DIK_K))			// key K
	{
		Eye(-1.0f, 'y');
	}
}