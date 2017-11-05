//*****************************************************************************
//
// ライトクラス [LightClass.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _LIGHT_CLASS_H_
#define _LIGHT_CLASS_H_

#include "Main.h"

class LightClass
{
public:
	LightClass();
	LightClass(LightType type);
	~LightClass();

	void ChangeLight(LightType type);

private:

};





#endif // !_LIGHT_CLASS_H_
