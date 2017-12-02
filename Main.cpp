//*****************************************************************************
//
// ゲーム全体処理[main.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Engine.h"

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Field.h"
#include "Console.h"
#include "SceneManager.h"

using namespace std;

// 臨時

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
int					g_nCountFPS;						// FPSカウンタ
LPDIRECT3D9			g_pD3D = NULL;					// Direct3Dオブジェクト
LPDIRECT3DDEVICE9		g_pD3DDevice = NULL;				// Deviceオブジェクト(描画に必要)

//////////////////////////////////////////////////////////////////////////////////
Console*				g_Console;				// コンソール
SceneManager*			g_SceneManager;			// シンー管理？？？
// 臨時

//////////////////////////////////////////////////////////////////////////////////

//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitDiretX(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);

void	Updata(void);
void	Draw(HWND hwnd);
void	Release(void);

// 臨時


//*****************************************************************************
//
// メイン関数
//
//*****************************************************************************
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(timeGetTime());

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
		return -1;
	}

	// メッセージを出る為のコンソールを初期化
	g_Console = new Console();
	if (g_Console->GetConsoleStatue() == false)
	{
		// 初期化失敗ならば
		return E_FAIL;
	}

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
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))						//イベントと先生が呼んだ。
		{
			if (msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
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
				dwExecLastTime = dwCurrentTime;	//処理した時刻を保存

				// 更新処理
				Updata();

				// 描画処理
				Draw(hWnd);

				dwFrameCount++;	//処理回数のカウントを加算

				// 60フレームを確定
				if (dwFrameCount == 60)
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
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
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
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		MessageBox(hWnd, _T("Direct3D初期化は失敗しました！"), _T("Main Error 1"), 0);		// エラーメッセージ
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		MessageBox(hWnd, _T("ディスプレイモードを取得できません！"), _T("Main Error 2"), 0);		// エラーメッセージ
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));					// ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;			// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.BackBufferCount = 1;							// バックバッファの数
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = bWindow;							// ウィンドウモード
	d3dpp.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;		// デプスバッファとして16bitを使う
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
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
	}

	D3DCAPS9 caps; int vp = 0;
	if (FAILED(g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;   //支持硬件顶点运算，我们就采用硬件顶点运算，妥妥的
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING; //不支持硬件顶点运算，无奈只好采用软件顶点运算


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
void Updata(void)
{
	// 入力更新
	UpdateInput();

	// シンーを更新する
	g_SceneManager->Update();
}

//*****************************************************************************
//
// 描画処理
//
//*****************************************************************************
void Draw(HWND hwnd)
{
	// シンーをドロー
	g_SceneManager->Draw();
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
