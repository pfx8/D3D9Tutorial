//*****************************************************************************
//
// ���b�Z�[�W�N���X [MessageClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESSAGE_CLASS_H_
#define _MESSAGE_CLASS_H_

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class OutputMessage
{
private:
	LPD3DXFONT			m_Font;	// �t�H���g�̃|�C���^

public:
	OutputMessage();
	~OutputMessage();

	void DrawPosMessage(const char name[], D3DXVECTOR3 OutputPos, D3DXVECTOR2 MessagePos);

};

#endif // !_MESSAGE_CLASS_H_
