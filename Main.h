//=============================================================================
//
// ゲーム全体処理[main.cpp]
// Author : リョウ　カンシン
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <d3dx9.h>
#include <tchar.h>

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
#define SCREEN_WIDTH		(960)							// ウインドウの幅
#define SCREEN_HEIGHT		(540)							// ウインドウの高さ
#define SCREEN_HALF_X		(SCREEN_WIDTH / 2)				// ウインドウの中心Ｘ座標
#define SCREEN_HALF_Y		(SCREEN_HEIGHT / 2)				// ウインドウの中心Ｙ座標

#define	NUM_VERTEX			(4)								// 頂点数
#define	NUM_POLYGON			(2)								// ポリゴン数

// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//D3DFVF_TEX1　テクスチャー座標

#define SAFE_RELEASE(ptr)					{ if(ptr) { (ptr)->Release(); (ptr) = NULL; } }

#endif