﻿//*****************************************************************************
//
// ゲーム全体処理[main.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Engine.h"

#include "Modules/Character.h"
#include "Modules/Camera.h"
#include "Modules/Light.h"
#include "Modules/Plane.h"
#include "Modules/Sound.h"
#include "Console.h"
#include "SceneManager.h"

using namespace std;

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
int					g_nCountFPS;						// FPSカウンタ
LPDIRECT3D9			g_pD3D = NULL;					// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;				// Deviceオブジェクト(描画に必要)

//////////////////////////////////////////////////////////////////////////////////
Console*			g_Console;				// コンソール
SceneManager*		g_SceneManager;			// シンー管理？？？
// 臨時

//////////////////////////////////////////////////////////////////////////////////

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void	Updata(HWND hWnd, int cmd);
void	Draw(HWND hWnd);
void	Release(void);

// 臨時


//*****************************************************************************
//
// メイン関数
//
//*****************************************************************************
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//srand(timeGetTime());
	srand((unsigned)time(NULL));

	// ウィンドウを初期化
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//時間計測用(*35)
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//フレームカウント初期化(*35)
	timeBeginPeriod(1);		//分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();		//ミリ秒単位で取得 syutoku
	dwCurrentTime = dwFrameCount = 0;

	//*****************************************************************************
	//
	// ウィンドウの設定
	//
	//*****************************************************************************
	
	// ウィンドウ属性を設定
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

	HWND		hWnd;	// ハンドル
	MSG		msg;		// メッセージ

	// ウィンドウクラスの登録
	if (!RegisterClassEx(&wcex))
		return -1;



	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		SCREEN_WIDTH,																		// ウィンドウ横幅
		SCREEN_HEIGHT,																		// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	//*****************************************************************************
	//
	// 各初期化
	//
	//*****************************************************************************
	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(InitDiretX(hInstance, hWnd, true)))
	{
		return E_FAIL;
	}

	// メッセージを出る為のコンソールを初期化
	g_Console = new Console();
	if (g_Console->isConsoleRun == false)
	{
		std::cout << "[Error] コンソールが初期化失敗!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 音楽
	InitSound(hWnd);

	// シンーマネジメント
	g_SceneManager = new SceneManager();

	//ヴインドウを中心に移動
	RECT rect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	MoveWindow(hWnd,
		(rect.right - rect.left - SCREEN_WIDTH) / 2,
		(rect.bottom - rect.top - SCREEN_HEIGHT) / 2,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		true);

	// ウインドウの表示(InitDiretX()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	//イベントと先生が呼んだ。
		{
			if (msg.message == WM_QUIT)
			{
				// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{
			dwCurrentTime = timeGetTime();	//1ミリ秒単位

			if ((dwCurrentTime - dwFPSLastTime) >= 500)	//0.5秒ごとに実行
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);	//FPSを計測

				dwFPSLastTime = dwCurrentTime;	//FPS計測時刻を保存

				dwFrameCount = 0;	//カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	//1/60秒ごとに実行
			{
				/*char str[256] = {};
				sprintf(str, _T("Under the sky ... %d"), g_nCountFPS);
				SetWindowText(hWnd, str);*/
				dwExecLastTime = dwCurrentTime;	//処理した時刻を保存
				Updata(hWnd, nCmdShow);						// 更新処理
				Draw(hWnd);					// 描画処理
				dwFrameCount++;				//処理回数のカウントを加算
				if (dwFrameCount == 60)		// 60フレームを確定
					continue;
			}
		}
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Release();

	return (int)msg.wParam;
}

//*****************************************************************************
//
// プロシージャ
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static float fog_start = 50;
	static float fog_end = 300;
	static float fog_density = 0.01f;

	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		Draw(hWnd);
		ValidateRect(hWnd, NULL);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:			// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//*****************************************************************************
//
// 初期化処理
//
//*****************************************************************************
HRESULT InitDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		std::cout << "[Error] DirectXオブジェクトが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		std::cout << "[Error] ディスプレイモードを取得できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ワークをゼロクリア


	D3DMULTISAMPLE_TYPE multiSampType = D3DMULTISAMPLE_NONE; // デフォルトで使わない
	if (g_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8B8G8R8,
		0, D3DMULTISAMPLE_4_SAMPLES, NULL))
	{
		multiSampType = D3DMULTISAMPLE_4_SAMPLES; // 4倍
	}

	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.MultiSampleType = multiSampType;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = bWindow;							// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		// デプスバッファとして16bitを使う
	d3dpp.Flags = 0;

	if (bWindow)
	{
		// ウィンドウモード
		// d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else
	{
		// フルスクリーンモード
		// d3dpp.BackBufferFormat = D3DFMT_R5G6B5;					// バックバッファ
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	D3DCAPS9 caps; 
	int vp = 0;
	if (FAILED(g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		std::cout << "[Error] DirectXオハードウェアの能力表が取得できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;	// ハードウェアで頂点を処理する
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	// ソフトウェアで頂点を処理する

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,							// ディスプレイアダプタ
		D3DDEVTYPE_HAL,								// ディスプレイタイプ
		hWnd,										// フォーカスするウインドウへのハンドル
		vp,											// デバイス作成制御の組み合わせ
		&d3dpp,										// デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))							// デバイスインターフェースへのポインタ
	{
		std::cout << "[Error] DirectXデバイスが生成できない!" << std::endl;	// エラーメッセージ
		return E_FAIL;
	}

	RELEASE_POINT(g_pD3D); // リリースLPDIRECT3D9

	//*****************************************************************************
	//
	// input
	//
	//*****************************************************************************
	InitInput(hInstance, hWnd);

	return S_OK;
}

//*****************************************************************************
//
// 更新処理
//
//*****************************************************************************
void Updata(HWND hWnd, int cmd)
{
	// ウィンドウからコンソールに変更
	if (GetKeyboardRelease(DIK_8) && g_Console->isConsoleFront == false)
	{
		//g_Console->SetConsoleFront(hWnd);
	}
	if (GetKeyboardRelease(DIK_8) && g_Console->isConsoleFront == true)
	{
		//g_Console->SetConsoleBack(hWnd, cmd);
	}

	if (g_Console->isConsoleFront == false)
	{
		UpdateInput();			// 入力更新
		g_SceneManager->Update();	// シンーを更新する
	}
}

//*****************************************************************************
//
// 描画処理
//
//*****************************************************************************
void Draw(HWND hWnd)
{
	if (g_Console->isConsoleFront == false)
	{
		g_SceneManager->Draw();	// シンーをドロー
	}
}

//*****************************************************************************
//
// 終了処理
//
//*****************************************************************************
void Release(void)
{
	// ポインタ
	RELEASE_POINT(g_pD3D);
	RELEASE_POINT(g_pD3DDevice);

	// 入力処理の終了処理
	UninitInput();

	// コンソールの終了処理
	RELEASE_CLASS_POINT(g_Console);
	RELEASE_CLASS_POINT(g_SceneManager);
}

//*****************************************************************************
//
// デバイス取得関数
//
// 他のファイルの中に、グローバル変数を渡すとき、こういうGET関数が必要だ。
//
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
