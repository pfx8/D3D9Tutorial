//*****************************************************************************
//
// マテリアル処理 [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "../Engine.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Material
{
private:


public:
	D3DMATERIAL9*	materialPoint;	// マテリアル情報へのポインタ
	DWORD			materialNum;		// マテリアル情報の数
	LPD3DXBUFFER	materialBuffer;	// マテリアルバッファ

	Material();
	~Material();
};

#endif // !_MATERIAL_H
