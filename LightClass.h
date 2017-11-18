//*****************************************************************************
//
// ライトクラス [LightClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _LIGHT_CLASS_H_
#define _LIGHT_CLASS_H_

#include "Main.h"

class Light
{
public:
	Light();
	Light(LightType type);
	~Light();

	void ChangeLight(LightType type);

private:

};
#endif // !_LIGHT_CLASS_H_
