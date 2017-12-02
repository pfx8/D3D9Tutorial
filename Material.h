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


public:
	D3DMATERIAL9*		m_materialPoint;	// マテリアル情報へのポインタ
	DWORD			m_materialNum;	// マテリアル情報の数

	Material();
	~Material();

	void SetMaterial();
};

#endif // !_MATERIAL_H
