//*****************************************************************************
//
// �ʗp�f�[�^���w�b�h�t�@�C��[Engine.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#ifndef _ENGINE_H_
#define _ENGINE_H_

//*****************************************************************************
//
// �w�b�h�t�@�C��
//
//*****************************************************************************
// Dx9
#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h>
#include <dinput.h>
#include "input.h"

// c++
#include <iostream>
#include <string>

// ����w�b�h�t�@�C��


//*****************************************************************************
//
// �ˑ��t�@�C��
//
//*****************************************************************************
#if 1	// [������"0"�ɂ����ꍇ�A"�\���v���p�e�B" -> "�����J" -> "����" -> "�ǉ��̈ˑ��t�@�C��"�ɑΏۃ��C�u������ݒ肷��]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
//
// �}�N����`
//
//*****************************************************************************
#define CLASS_NAME			_T("D3d9Class")				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		_T("Zilch-E")					// �E�C���h�E�̃L���v�V������
#define SCREEN_WIDTH		(960)						// �E�C���h�E�̕�
#define SCREEN_HEIGHT		(540)						// �E�C���h�E�̍���

// ���_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	FVF_VERTEX_3D_NT	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE)

#define RELEASE_POINT(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
#define RELEASE_CLASS_POINT(ptr)			{ if(ptr) { delete ptr; } }
#define RELEASE_CLASS_ARRY_POINT(ptr)		{ if(ptr) { delete [] ptr;} }

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

//*****************************************************************************
//
// �\���̒�`
//
//*****************************************************************************
// 3D���_
typedef struct VERTEX_3D
{
	// ���_���̕ϐ��̏��Ԃ͒��_�t�H�[�}�b�g�̂Ɠ���
	D3DXVECTOR3 position;			// ���_���W
	D3DXVECTOR3 normalVector;		// �@���x�N�g��
	D3DCOLOR diffuse;				// ���ˌ�
	D3DXVECTOR2 texturePosition;	// �e�N�X�`�����W
}VERTEX_3D;

typedef struct VERTEX_3D_NT
{
	// ���_���̕ϐ��̏��Ԃ͒��_�t�H�[�}�b�g�̂Ɠ���
	D3DXVECTOR3 position;			// ���_���W
	D3DXVECTOR3 normalVector;		// �@���x�N�g��
	D3DCOLOR diffuse;				// ���ˌ�
}VERTEX_3D_NT;

// �e�N�X�`���\����
typedef struct TextureStruct
{
	const char*			Name;			// �e�N�X�`�����O
	const char*			Path;			// �e�N�X�`���p�X
	LPDIRECT3DTEXTURE9		TexturePoint;		// �e�N�X�`���|�C���^
}TextureStruct;

//*****************************************************************************
//
// �񋓑̒�`
//
//*****************************************************************************
typedef enum LightType
{
	LT_PointLight,
	LT_DirectionalLight,
	LT_SpotLight,
}LightType;

//*****************************************************************************
//
// �v���g�^�C�v�錾
//
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);

#endif // !_ENGINE_H_