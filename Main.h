//*****************************************************************************
//
// �Q�[���S�̏���[main.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~

#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>
#include <time.h>

#include <iostream>
#include <map>
#include <string>

#include <dinput.h>

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
#define SCREEN_WIDTH		(960)						// �E�C���h�E�̕�
#define SCREEN_HEIGHT		(540)						// �E�C���h�E�̍���

// ���_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //D3DFVF_TEX1�@�e�N�X�`���[���W

#define SAFE_RELEASE_POINT(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
#define SAFE_RELEASE_CLASS_POINT(cptr)			{ if(cptr) { delete cptr; } }

#define	NUM_VERTEX		(4)		// ���_��
#define	NUM_POLYGON		(2)		// �|���S����

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct VERTEX_3D
{
	// ���_���̕ϐ��̏��Ԃ͒��_�t�H�[�}�b�g�̂Ɠ���
	D3DXVECTOR3 Position;			// ���_���W
	D3DXVECTOR3 NormalVector;		// �@���x�N�g��
	D3DCOLOR diffuse;				// ���ˌ�
	D3DXVECTOR2 TexturePosition;	// �e�N�X�`�����W
}VERTEX_3D;

// �e�N�X�`���\����
typedef struct Texture
{
	const char*				Name;			// �e�N�X�`�����O
	const char*				Path;			// �e�N�X�`���p�X
	LPDIRECT3DTEXTURE9		TexturePoint;	// �e�N�X�`���|�C���^
}Texture;

//*****************************************************************************
// �񋓑̒�`
//*****************************************************************************
typedef enum ExampleType
{
	ET_Vertex,
	ET_Light,
	ET_SampleMesh,
}ExampleType;

typedef enum LightType
{
	LT_PointLight,
	LT_DirectionalLight,
	LT_SpotLight,
}LightType;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
LPDIRECT3DVERTEXBUFFER9 *GetVertexBuffer(void);
LPDIRECT3DINDEXBUFFER9 *GetIndexBuffer(void);

#endif