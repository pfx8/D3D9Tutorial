//*****************************************************************************
//
// �f�o�b�N���b�Z�[�W���� [DebugMessage.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "DebugMessage.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
DebugMessage::DebugMessage()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	m_Font = NULL;

	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_Font);
}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
DebugMessage::~DebugMessage()
{
	SAFE_RELEASE_POINT(m_Font);
}

//*****************************************************************************
//
// ������`�悷��
//
//*****************************************************************************
void DebugMessage::DrawPosMessage(const char name[], D3DXVECTOR3 OutputPos, D3DXVECTOR2 MessagePos)
{
	RECT rectCoor = { int(MessagePos.x), int(MessagePos.y), SCREEN_WIDTH, SCREEN_HEIGHT };
	char str[256];

	// ����������
	sprintf(str, _T("%s\nX:%.2f,Y:%.2f,Z:%.2f"), name, OutputPos.x, OutputPos.y, OutputPos.z);

	// �������`�悷��
	m_Font->DrawText(NULL, &str[0], -1, &rectCoor, DT_LEFT, D3DCOLOR_RGBA(255, 0, 255, 0xff));

}