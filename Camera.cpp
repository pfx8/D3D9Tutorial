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
	m_posEye		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posAt		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_vecUp		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecLook		= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_vecRight	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_vecFromEyeToAt		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXMatrixIdentity(&m_viewMatrix);
	D3DXMatrixIdentity(&m_projectionMatrix);

	m_message = new DebugMessage();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Camera::~Camera()
{
	RELEASE_CLASS_POINT(m_message);
}



//*****************************************************************************
//
// カメラを初期化する
//
//*****************************************************************************
void Camera::InitCamera(D3DXVECTOR3 Eye, D3DXVECTOR3 At, D3DXVECTOR3 Up)
{
	
	m_posEye = Eye;	// カメラの視点を初期化する
	m_posAt = At;		// カメラの注視点を初期化する
	m_vecUp = Up;		// カメラの上方向ベクトル、一般には (0, 1, 0) を定義する 

	m_vecFromEyeToAt = m_posEye - m_posAt;
}

//*****************************************************************************
//
// 注視点座標を更新
//
//*****************************************************************************
void Camera::UpdateAt(D3DXVECTOR3 pos)
{
	m_posAt = pos;
	//m_posEye = m_vecFromEyeToAt + pos;
}

//*****************************************************************************
//
// ビューイング変換
//
//*****************************************************************************
void Camera::SetViewMatrix()
{
	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_posEye, &m_posAt, &m_vecUp);

	// ビューマトリックスの設定
	GetDevice()->SetTransform(D3DTS_VIEW, &m_viewMatrix);
}

//*****************************************************************************
//
// プロジェクション変換(投影変換)
//
//*****************************************************************************
void Camera::SetProjMatrix()
{
	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix,
		D3DXToRadian(45.0f),						// ビュー平面の視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// ビュー平面のアスペクト比
		10.0f,									// ヒュー平面のNearZ値
		1000.0f);									// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix);
}

//*****************************************************************************
//
// ビューポートを設定
//
//*****************************************************************************
void Camera::SetViewport()
{
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;

	// ヒューポットを設定
	GetDevice()->SetViewport(&vp);
}

//*****************************************************************************
//
// カメラ更新
//
//*****************************************************************************
void Camera::Update()
{
	if (GetKeyboardPress(DIK_J))	// key J
	{
		RotationVecUp(1.0f / 180.0f * D3DX_PI);
	}
	if (GetKeyboardPress(DIK_L))	// key L
	{
		RotationVecUp(-1.0f / 180.0f * D3DX_PI);
	}
	if (GetKeyboardPress(DIK_I))	// key I
	{
		RotationVecRight(1.0f / 180.0f * D3DX_PI);
	}
	if (GetKeyboardPress(DIK_K))	// key K
	{
		RotationVecRight(-1.0f / 180.0f * D3DX_PI);
	}

	if (GetKeyboardPress(DIK_LEFT))
	{
		MoveAlongVecRight(-1.0f);
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		MoveAlongVecRight(1.0f);
	}
	if (GetKeyboardPress(DIK_UP))
	{
		MoveAlongVecLook(1.0f);
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		MoveAlongVecLook(-1.0f);
	}

	// ビューイング変換
	SetViewMatrix();
}

//*****************************************************************************
//
// 上方向のベクトルにして回転
//
//*****************************************************************************
void Camera::RotationVecUp(float angle)
{
	if (m_rot.y > D3DX_PI * 2.0f || m_rot.y < -D3DX_PI * 2.0f)
	{
		m_rot.y = 0;
	}

	// 角度を記録する
	m_rot.y -= angle;

	// 新しい右方向ベクトルを計算する
	m_vecRight.x = cosf(m_rot.y);
	m_vecRight.z = sinf(m_rot.y);

	// 新しい注視方向ベクトルを計算する
	m_vecLook.x = cosf(m_rot.y + D3DX_PI / 2);
	m_vecLook.z = sinf(m_rot.y + D3DX_PI / 2);

	m_posEye.x = m_posEye.x * cosf(angle) + m_posEye.z * sinf(angle);
	m_posEye.z = -m_posEye.x * sinf(angle) + m_posEye.z * cosf(angle);
}

//*****************************************************************************
//
// 右方向のベクトルにして回転
//
//*****************************************************************************
void Camera::RotationVecRight(float angle)
{
	// 角度の移動範囲は -55 + 45(初期) ~ 45(初期) + 20
	if (m_rot.x >= 20.0f / 180.0f * D3DX_PI && angle < 0)
	{
		m_rot.x = 20.0f / 180.0f * D3DX_PI;
	}
	else if(m_rot.x <= -55.0f / 180.0f * D3DX_PI && angle > 0)
	{ 
		m_rot.x = -55.0f / 180.0f * D3DX_PI;
	}
	else
	{
		// 角度を記録する
		m_rot.x -= angle;

		// 注視ベクトルを更新する
		m_vecLook.z = cosf(m_rot.x);
		m_vecLook.y = sinf(m_rot.x);

		// 上方向ベクトルを更新する
		m_vecUp.z = cosf(m_rot.x + D3DX_PI / 2);
		m_vecUp.y = sinf(m_rot.x + D3DX_PI / 2);

		// カメラ位置を更新する
		m_posEye.z = m_posEye.z * cosf(angle) - m_posEye.y * sinf(angle);
		m_posEye.y = m_posEye.z * sinf(angle) + m_posEye.y * cosf(angle);
	}
}

//*****************************************************************************
//
// 右方向に沿って移動
//
//*****************************************************************************
void Camera::MoveAlongVecRight(float unit)
{
	m_posEye += m_vecRight * unit;
	m_posAt += m_vecRight * unit;
}

//*****************************************************************************
//
// 注視方向に沿って移動
//
//*****************************************************************************
void Camera::MoveAlongVecLook(float unit)
{
	m_posEye += m_vecLook * unit;
	m_posAt += m_vecLook * unit;
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Camera::PosToMessageAndMessageDraw(int row)
{
	m_message->DrawPosMessage("CameraEye", m_posEye, D3DXVECTOR2(0, float((row + 1)* 18 * 2)));
	m_message->DrawPosMessage("CameraAt", m_posAt, D3DXVECTOR2(0, float((row + 2) * 18 * 2)));
	m_message->DrawPosMessage("->VecLook", m_vecLook, D3DXVECTOR2(0, float((row + 4) * 18 * 2)));
	m_message->DrawPosMessage("->VecRight", m_vecRight, D3DXVECTOR2(0, float((row + 5) * 18 * 2)));
	m_message->DrawPosMessage("VecUp", m_vecUp, D3DXVECTOR2(0, float((row + 6) * 18 * 2)));
	m_message->DrawPosMessage("Rot Radian", m_rot, D3DXVECTOR2(0, float((row + 8) * 18 * 2)));
	m_message->DrawPosMessage("Rot Degree", D3DXVECTOR3(0.0f, D3DXToDegree(m_rot.x), 0.0f), D3DXVECTOR2(0, float((row + 9) * 18 * 2)));
}