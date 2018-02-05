﻿//*****************************************************************************
//
// ライト処理 [Light.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Light.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Light::Light()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 平行光源を初期化
	::ZeroMemory(&m_light, sizeof(m_light));	// m_light変数のメモリを初期化

	m_light.Type = D3DLIGHT_DIRECTIONAL;

	m_light.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f) * 3.0f;	// アンビエント(環境光のカラー)
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 拡散反射光(モデル本来のカラー)
	m_light.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);	// 鏡面反射光

	m_light.Direction = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);		// 光の方向

	pDevice->SetLight(0, &m_light);
	pDevice->LightEnable(0, true);
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Light::~Light()
{

}