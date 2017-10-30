//=============================================================================
//
// 品物の質感クラス [Material.cpp]
// Author : リョウ　カンシン
//
//=============================================================================
#include "Material.h"

Material::Material()
{
	
}

Material::~Material()
{
}

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