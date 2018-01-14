//*****************************************************************************
//
// ���C�g���� [Light.h]
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
// �N���X�錾
//
//*****************************************************************************
class Light
{
private:
	D3DXVECTOR3	m_rot;				// �������̉�]�p�x
	DebugMessage* mes;
public:
	D3DXVECTOR3	m_directionlight;		// �������x�N�g��

	Light();	
	~Light();

	void RotationY(float angle);		// Y�����̃x�N�g���ɂ��ĉ�]
	void message(int row);
};
#endif // !_LIGHT_H_
