//*****************************************************************************
//
// マテリアル処理 [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Material
{
private:
	LPD3DXBUFFER		m_D3DXBuffMatModel;	// マテリアル情報へのポインタ
	DWORD			m_NumMatModel;		// マテリアル情報の数

public:
	Material();
	~Material();

	void SetMaterial();

	LPD3DXBUFFER* GetMaterialPoint();		// m_D3DXBuffMatModelの取得
	DWORD* GetMterialNumber();				// m_NumMatModelの取得
};

#endif // !_MATERIAL_H
