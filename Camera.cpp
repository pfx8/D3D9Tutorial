//=============================================================================
//
// カメラクラス [Camera.cpp]
// Author : リョウ　カンシン
//
//=============================================================================
#include "Camera.h"
#include "Main.h"


//*****************************************************************************
// コンストラクタ
//*****************************************************************************
Camera::Camera()
{

}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
Camera::~Camera()
{

}

//*****************************************************************************
// Step1 世界座標から変更
//*****************************************************************************
void Camera::setWorldMatrix()
{
	D3DXMATRIX matWorld, Rx, Ry, Rz;

	// 単位行列を作成する
	D3DXMatrixIdentity(&matWorld);

	// X軸に回転
	//D3DXMatrixRotationX(&Rx, D3DX_PI * (timeGetTime() / 1000.0f));

	// Y軸に回転
	D3DXMatrixRotationY(&Ry, D3DX_PI * (timeGetTime() / 1440.0f));

	// Z軸に回転
	//D3DXMatrixRotationZ(&Rz, D3DX_PI * (timeGetTime() / 1000.0f / 3));

	//matWorld = Rx * Ry * Rz * matWorld;

	matWorld = Ry * matWorld;

	GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
}

//*****************************************************************************
// Step2 
//*****************************************************************************
void Camera::setViewMatrix()
{
	D3DXMATRIX matView;

	// 視点を定義する
	D3DXVECTOR3 vEye(0.0f, 0.0f, -200.0f);

	// カメラの注視対象を定義する
	D3DXVECTOR3 vAt(0.0f, 0.0f, 0.0f);

	// カレントワールドの上方、一般には [0, 1, 0] を定義する 
	D3DXVECTOR3 vUp(0.0f, 1.0f,0.0f);

	// 左手座標系ビュー行列を作成する
	D3DXMatrixLookAtLH(&matView, &vEye, &vAt, &vUp);

	GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}
//*****************************************************************************
// Step3
//*****************************************************************************
void Camera::setProjMatrix()
{
	D3DXMATRIX matProj;

	// 左手座標系パースペクティブ射影行列を作成する
	D3DXMatrixPerspectiveLH(&matProj, D3DX_PI / 4.0f, 1.0f, 1.0f, 1000.0f);

	GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
}
//*****************************************************************************
// Step4
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