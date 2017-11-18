//*****************************************************************************
//
// ゲーム全体処理[main.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止

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

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#endif

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			_T("D3d9Class")				// ウインドウのクラス名
#define WINDOW_NAME			_T("Zilch-E")				// ウインドウのキャプション名
#define SCREEN_WIDTH		(960)						// ウインドウの幅
#define SCREEN_HEIGHT		(540)						// ウインドウの高さ

// 頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1) //D3DFVF_TEX1　テクスチャー座標
#define	FVF_VERTEX_3D_NT	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE) //D3DFVF_TEX1　テクスチャー座標

#define SAFE_RELEASE_POINT(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }
#define SAFE_RELEASE_CLASS_POINT(cptr)			{ if(cptr) { delete cptr; } }

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 3D頂点
typedef struct VERTEX_3D
{
	// 頂点楮体変数の順番は頂点フォーマットのと同じ
	D3DXVECTOR3 Position;			// 頂点座標
	D3DXVECTOR3 NormalVector;		// 法線ベクトル
	D3DCOLOR diffuse;				// 反射光
	D3DXVECTOR2 TexturePosition;	// テクスチャ座標
}VERTEX_3D;

// 3D頂点(テクスチャ無し)
typedef struct VERTEX_3D_NT
{
	// 頂点楮体変数の順番は頂点フォーマットのと同じ
	D3DXVECTOR3 Position;			// 頂点座標
	D3DXVECTOR3 NormalVector;		// 法線ベクトル
	D3DCOLOR diffuse;				// 反射光
}VERTEX_3D_NT;

// テクスチャ構造体
typedef struct Texture
{
	const char*				Name;			// テクスチャ名前
	const char*				Path;			// テクスチャパス
	LPDIRECT3DTEXTURE9		TexturePoint;	// テクスチャポインタ
}Texture;

//*****************************************************************************
// 列挙体定義
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
// プロトタイプ宣言
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);

#endif