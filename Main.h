//=============================================================================
//
// �Q�[���S�̏���[main.cpp]
// Author : �����E�@�J���V��
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>

#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			_T("D3d9Class")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME			_T("Zilch-E")				// �E�C���h�E�̃L���v�V������
#define SCREEN_WIDTH		(960)							// �E�C���h�E�̕�
#define SCREEN_HEIGHT		(540)							// �E�C���h�E�̍���
#define SCREEN_HALF_X		(SCREEN_WIDTH / 2)				// �E�C���h�E�̒��S�w���W
#define SCREEN_HALF_Y		(SCREEN_HEIGHT / 2)				// �E�C���h�E�̒��S�x���W

#define	NUM_VERTEX			(4)								// ���_��
#define	NUM_POLYGON			(2)								// �|���S����

// ���_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//D3DFVF_TEX1�@�e�N�X�`���[���W

#define SAFE_RELEASE(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

#endif