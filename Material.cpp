﻿//*****************************************************************************
//
// マテリアル処理 [Material.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Material.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Material::Material()
{
	m_materialPoint = NULL;
	m_materialNum = 0;
	m_materialBuffer = NULL;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Material::~Material()
{
	RELEASE_CLASS_POINT(m_materialPoint); 
}

//*****************************************************************************
//
// マテリアルを設定
//
//*****************************************************************************
void Material::SetMaterial()
{
	D3DMATERIAL9 mtrl;

	ZeroMemory(&mtrl, sizeof(mtrl));

	// 環境光を設定
	mtrl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.7f, 1.0f);

	// 拡散光を設定
	mtrl.Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);

	// 鏡面光を設定,スペキュラハイライト
	mtrl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);

	// 放射光を設定(自分から光が出る)
	mtrl.Emissive = D3DXCOLOR(0.3f, 0.0f, 0.1f, 1.0f);

	GetDevice()->SetMaterial(&mtrl);
}