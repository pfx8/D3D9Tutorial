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
	this->field = D3DXToRadian(45);
	this->ratio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;;
	this->rangeStart = 0.1;
	this->rangeEnd = 1000;

	this->posEye	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->posAt		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->upVector		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector	= D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	this->rightVector	= D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	this->offsetFromTargetMin = 15.0f;
	this->offsetFromTargetMax = 75.0f;
	this->verticalRadiansMin = -0.2f;
	this->verticalRadiansMax = 0.8f;

	this->rotateSpeedHorizonal = 2.0f;
	this->rotateSpeedVertical = 1.0f;
	this->zoomSpeed = 4.0f;

	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projectionMatrix);

	this->message = new DebugMessage();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Camera::~Camera()
{
	RELEASE_CLASS_POINT(this->message);
}

//*****************************************************************************
//
// カメラを初期化する
//
//*****************************************************************************
void Camera::InitCameraByPlayer(Character* player)
{	
	this->posEye = player->m_lookVector + D3DXVECTOR3(0.0f, 10.0f, 35.0f);
	this->posAt = player->m_pos + D3DXVECTOR3(0.0f, 5.0f, 0.0f);

	//this->lookVector = player->m_lookVector;
	//this->rightVector = player->m_rightVector;

	this->offSetFromPlayer = player->m_pos - this->posEye;

	SetViewport();		// ビューポートを設定
}


//*****************************************************************************
//
// カメラ更新
//
//*****************************************************************************
void Camera::Update(Character* player)
{
	// プレーヤーによってカメラを更新
	//this->posEye += player->m_lookVector * player->m_speedCoefficient;
	//this->posAt += player->m_lookVector * player->m_speedCoefficient;

	// カメラ位置を更新
	this->posEye = player->m_pos - this->offSetFromPlayer;
	this->posAt += player->m_lookVector * player->m_speedCoefficient;

	// カメラベクトルを更新
	D3DXVECTOR3 temp = player->m_pos - this->posEye;
	D3DXVec3Normalize(&this->lookVector, &temp);
	D3DXVec3Cross(&this->rightVector, &this->lookVector, &player->m_upVector);
	D3DXVec3Normalize(&this->rightVector, &this->rightVector);
	D3DXVec3Cross(&this->upVector, &this->rightVector, &this->lookVector);
	D3DXVec3Normalize(&this->upVector, &this->upVector);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&this->viewMatrix, &this->posEye, &this->posAt, &this->upVector);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&this->projectionMatrix,
								this->field,   	// ビュー平面の視野角
								this->ratio,		// ビュー平面のアスペクト比
								this->rangeStart,	// ヒュー平面のNearZ値
								this->rangeEnd);	// ビュー平面のFarZ値
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
// 回転操作
//
//*****************************************************************************
void Camera::Rotation(Character* player, float radiansHorizonal, float radiansVertical)
{
	// 水平

	// 垂直
}

//*****************************************************************************
//
// ズーム操作
//
//*****************************************************************************
void Camera::Zoom(float distance)
{
	D3DXVECTOR3 zoomDistance = this->lookVector * distance;			// 変更量を計算
	D3DXVECTOR3	tempOffset = this->offSetFromPlayer + zoomDistance;	// 新しい偏り量を計算

	float radians = D3DXVec3Length(&tempOffset);	// 半径を計算
	if (radians < this->offsetFromTargetMax && radians > this->offsetFromTargetMin)
	{
		// 半径は範囲内ならば、偏り量を更新
		this->offSetFromPlayer = tempOffset;
	}
}

////*****************************************************************************
////
//// 上方向のベクトルにして回転
////
////*****************************************************************************
//void Camera::RotationVecUp(float angle)
//{
//	if (rot.y > D3DX_PI * 2.0f || rot.y < -D3DX_PI * 2.0f)
//	{
//		rot.y = 0;
//	}
//
//	// 角度を記録する
//	rot.y -= angle;
//
//	// 新しい右方向ベクトルを計算する
//	rightVector.x = cosf(rot.y);
//	rightVector.z = sinf(rot.y);
//
//	// 新しい注視方向ベクトルを計算する
//	lookVector.x = cosf(rot.y + D3DX_PI / 2);
//	lookVector.z = sinf(rot.y + D3DX_PI / 2);
//
//	D3DXMATRIX rotMatrix;
//	D3DXMatrixRotationAxis(&rotMatrix, &upVector, angle);		// 回転行列を作る
//	D3DXVec3TransformCoord(&posEye, &posEye, &rotMatrix);	// 回転行列で新しい座標を計算する
//}
//
////*****************************************************************************
////
//// 右方向のベクトルにして回転
////
////*****************************************************************************
//void Camera::RotationVecRight(float angle)
//{
//	// 角度の移動範囲は -55 + 45(初期) ~ 45(初期) + 20
//	if (rot.x >= 20.0f / 180.0f * D3DX_PI && angle < 0)
//	{
//		rot.x = 20.0f / 180.0f * D3DX_PI;
//	}
//	else if(rot.x <= -55.0f / 180.0f * D3DX_PI && angle > 0)
//	{ 
//		rot.x = -55.0f / 180.0f * D3DX_PI;
//	}
//	else
//	{
//		// 角度を記録する
//		rot.x -= angle;
//
//		// 注視ベクトルを更新する
//		lookVector.z = cosf(rot.x);
//		lookVector.y = sinf(rot.x);
//
//		// 上方向ベクトルを更新する
//		upVector.z = cosf(rot.x + D3DX_PI / 2);
//		upVector.y = sinf(rot.x + D3DX_PI / 2);
//
//		// カメラ位置を更新する
//		posEye.z = posEye.z * cosf(angle) - posEye.y * sinf(angle);
//		posEye.y = posEye.z * sinf(angle) + posEye.y * cosf(angle);
//	}
//}


//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Camera::PosToMessageAndMessageDraw(int row)
{
	message->DrawPosMessage("look  ", this->lookVector, D3DXVECTOR2(0, float((row + 0) * 18)));
	message->DrawPosMessage("right ", this->rightVector, D3DXVECTOR2(0, float((row + 1) * 18)));
	message->DrawPosMessage("up    ", this->upVector, D3DXVECTOR2(0, float((row + 2) * 18)));
	message->DrawPosMessage("offset", this->offSetFromPlayer, D3DXVECTOR2(0, float((row + 3) * 18)));
}
