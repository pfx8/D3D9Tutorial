//=============================================================================
//
// ライトクラス [Light.h]
// Author : リョウ　カンシン
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H

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





#endif // !_LIGHT_H_
