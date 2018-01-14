//*****************************************************************************
//
// ライト処理 [Light.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "..\Engine.h"
#include "..\DebugMessage.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Light
{
private:
	D3DXVECTOR3	m_rot;				// 光方向の回転角度
	DebugMessage* mes;
public:
	D3DXVECTOR3	m_directionlight;		// 光方向ベクトル

	Light();	
	~Light();

	void RotationY(float angle);		// Y方向のベクトルにして回転
	void message(int row);
};
#endif // !_LIGHT_H_
