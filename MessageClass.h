//*****************************************************************************
//
// ���b�Z�[�W�N���X [MessageClass.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _MESSAGE_CLASS_H_
#define _MESSAGE_CLASS_H_

#include "Main.h"

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
