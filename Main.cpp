//=============================================================================
//
// �Q�[���S�̏���[main.cpp]
// Author : �����E�@�J���V��
//
//=============================================================================
#include "Main.h"
#include "Windows.h"

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �E�B���h�E��������
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

											// �E�B���h�E������ݒ�
	WNDCLASSEX	wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_CLASSDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = NULL;

	HWND		hWnd;
	MSG			msg;

	// �E�B���h�E�N���X�̓o�^
	if (!RegisterClassEx(&wcex))
		return -1;

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		SCREEN_WIDTH,																		// �E�B���h�E����
		SCREEN_HEIGHT,																		// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	//���C���h�E�𒆐S�Ɉړ�
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	MoveWindow(hWnd,
		(rect.right - rect.left - SCREEN_WIDTH) / 2,
		(rect.bottom - rect.top - SCREEN_HEIGHT) / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		true);

	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	// ���b�Z�[�W���[�v
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))						//�C�x���g�Ɛ搶���Ă񂾁B
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{

		}
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}