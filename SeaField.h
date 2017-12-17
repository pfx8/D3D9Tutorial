//*****************************************************************************
//
// äCñ èàóù [SeaField.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SEA_FIELD_H_
#define _SEA_FIELD_H_

#include "Modules\Plane.h"

class SeaField : public Plane
{
private:

public:
	SeaField();
	~SeaField();

	HRESULT InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum);
	void Draw(Shader* shader);
};

#endif // !_SEA_FIELD_H_
