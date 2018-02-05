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
	m_posAt			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_upVector		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookVector	= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_rightVector	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	m_isShooting	= false;
	m_radius		= 43.0f;

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
void Camera::InitCameraByPlayer(Character* player)
{	
	m_posEye = player->m_lookVector + D3DXVECTOR3(0.0f, 10.0f, 35.0f);
	m_posAt = player->m_pos + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_rot = player->m_rot;
	m_lookVector = player->m_lookVector;
	m_rightVector = player->m_rightVector;

	SetViewMatrix();	// ビューイング変換
	SetProjMatrix();	// プロジェクション変換
	SetViewport();		// ビューポートを設定
}

//*****************************************************************************
//
// ビューイング変換
//
//*****************************************************************************
void Camera::SetViewMatrix()
{	
	D3DXMatrixLookAtLH(&m_viewMatrix, &m_posEye, &m_posAt, &m_upVector);	// ビューマトリックスの作成
	GetDevice()->SetTransform(D3DTS_VIEW, &m_viewMatrix);				// ビューマトリックスの設定
}

//*****************************************************************************
//
// プロジェクション変換(投影変換)
//
//*****************************************************************************
void Camera::SetProjMatrix()
{
	D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, // プロジェクションマトリックスの作成
		D3DXToRadian(45.0f),						// ビュー平面の視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// ビュー平面のアスペクト比
		10.0f,										// ヒュー平面のNearZ値
		1000.0f);									// ビュー平面のFarZ値

	GetDevice()->SetTransform(D3DTS_PROJECTION, &m_projectionMatrix);	// プロジェクションマトリックスの設定
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

	GetDevice()->SetViewport(&vp);	// ヒューポットを設定
}

//*****************************************************************************
//
// キャラクターによってカメラを更新
//
//*****************************************************************************
void Camera::UpdateByPlayer(Character* player)
{
	// ship
	/*m_rot = player->m_rot;
	m_posEye.x = player->m_pos.x + cosf(m_rot.y + D3DX_PI / 2) * 25.0f;
	m_posEye.y = player->m_pos.y + 10.0f;
	m_posEye.z = player->m_pos.z + sinf(m_rot.y + D3DX_PI / 2) * 25.0f;*/
	//m_rot = player->m_rot;
	if (m_isShooting == false)
	{
		//m_posEye.x = player->m_pos.x + cosf(m_rot.y + D3DX_PI / 2) * m_radius;
		//m_posEye.y = player->m_pos.y + 10.0f;
		//m_posEye.z = player->m_pos.z + sinf(m_rot.y + D3DX_PI / 2) * m_radius;

		m_posAt = player->m_pos + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	}
	else if (m_isShooting == true)
	{
		m_posAt = player->m_pos + player->m_rightVector * m_radius;

		//m_posAt.x = (m_posEye.x - player->m_pos.x) / 2 + cosf(-D3DX_PI / 2) * m_radius;
		m_posAt.y = 0.0f;
		//m_posAt.z = (m_posEye.x - player->m_pos.z) / 2 + sinf(-D3DX_PI / 2) * m_radius;

		m_posEye.x = player->m_pos.x;
		m_posEye.y = player->m_pos.y + 8.0f;
		m_posEye.z = player->m_pos.z;
	}
	/*m_lookVector = player->m_lookVector;
	m_rightVector = player->m_rightVector;*/
	//player->m_lookVector = m_lookVector;
	//player->m_rightVector = m_rightVector;

	SetViewMatrix();	// ビューイング変換
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
	m_rightVector.x = cosf(m_rot.y);
	m_rightVector.z = sinf(m_rot.y);

	// 新しい注視方向ベクトルを計算する
	m_lookVector.x = cosf(m_rot.y + D3DX_PI / 2);
	m_lookVector.z = sinf(m_rot.y + D3DX_PI / 2);

	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationAxis(&rotMatrix, &m_upVector, angle);		// 回転行列を作る
	D3DXVec3TransformCoord(&m_posEye, &m_posEye, &rotMatrix);	// 回転行列で新しい座標を計算する

	SetViewMatrix();	// ビューイング変換
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
		m_lookVector.z = cosf(m_rot.x);
		m_lookVector.y = sinf(m_rot.x);

		// 上方向ベクトルを更新する
		m_upVector.z = cosf(m_rot.x + D3DX_PI / 2);
		m_upVector.y = sinf(m_rot.x + D3DX_PI / 2);

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
	m_posEye += m_rightVector * unit;
	m_posAt += m_rightVector * unit;
}

//*****************************************************************************
//
// 注視方向に沿って移動
//
//*****************************************************************************
void Camera::MoveAlongVecLook(float unit)
{
	// 判断
	m_posEye += m_lookVector * unit;

	SetViewMatrix();	// ビューイング変換
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Camera::PosToMessageAndMessageDraw(int row)
{
	//m_message->DrawPosMessage("C-look", m_lookVector, D3DXVECTOR2(0, float(row * 18)));
	//m_posEye.y = m_rot.y;
	m_message->DrawPosMessage("Pos", m_posEye, D3DXVECTOR2(0, float((row + 0) * 18)));
	//m_message->DrawPosMessage("Look", m_lookVector, D3DXVECTOR2(0, float((row + 1) * 18)));
}

//*****************************************************************************
//
// プレーヤーとカメラの半径を変わる
//
//*****************************************************************************
void Camera::isAtToEyeVectorMoreLong(bool isMoreLong)
{
	
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
void Camera::UpdateAngle(float angle)
{
	if (m_rot.y > D3DX_PI * 2.0f || m_rot.y < -D3DX_PI * 2.0f)
	{
		m_rot.y = 0;
	}

	m_rot.y -= angle;

	// 新しい右方向ベクトルを計算する
	m_rightVector.x = cosf(m_rot.y);
	m_rightVector.z = sinf(m_rot.y);

	// 新しい注視方向ベクトルを計算する
	m_lookVector.x = cosf(m_rot.y + D3DX_PI / 2);
	m_lookVector.z = sinf(m_rot.y + D3DX_PI / 2);
}

//*****************************************************************************
//
// 
//
//*****************************************************************************
void Camera::ChangeRadius(bool isPlus)
{
	if (isPlus == true)
	{
		m_radius += 0.05f;
	}
	else
	{
		m_radius -= 0.05f;
	}
}