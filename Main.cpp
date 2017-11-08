//*****************************************************************************
//
// ゲーム全体処理[main.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "Main.h"

#include "CharacterClass.h"
#include "CameraClass.h"
#include "MeshClass.h"
#include "LightClass.h"

//*****************************************************************************
//
// グローバル変数
//
//*****************************************************************************
int							g_nCountFPS;						// FPSカウンタ
LPDIRECT3D9					g_pD3D = NULL;						// Direct3Dオブジェクト
LPDIRECT3DDEVICE9			g_pD3DDevice = NULL;				// Deviceオブジェクト(描画に必要)

LPDIRECT3DVERTEXBUFFER9		g_pVertexBuffer = NULL;				// 頂点バッファ
LPDIRECT3DINDEXBUFFER9		g_pIndexBuffer = NULL;				// インデックスバッファ

Camera*				g_camera;							// カメラ
Mesh*				g_mesh;								// メッシュ(マテリアルを含む)
Light*				g_light;							// ライト

Character*			g_character;						// ゲーム素材


//*****************************************************************************
//
// プロトタイプ宣言
//
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitDiretX(HWND hWnd, BOOL bWindow);
HRESULT InitGameObject(void);
void	Updata(void);
void	Draw(HWND hwnd);
void	Release(void);

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

	HWND		hWnd;
	MSG			msg;

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

	// DirectXの初期化(ウィンドウを作成してから行う)
	if (FAILED(InitDiretX(hWnd, true)))
	{
		return -1;
	}

	// ゲーム素材を初期化する
	InitGameObject();

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
HRESULT InitDiretX(HWND hWnd, BOOL bWindow)
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

	SAFE_RELEASE_POINT(g_pD3D); // リリースLPDIRECT3D9

	return S_OK;
}

//*****************************************************************************
//
// 初期化処理
//
//*****************************************************************************
HRESULT InitGameObject(void)
{
	// カメラを初期化
	g_camera = new Camera();
	g_camera->InitCamera(D3DXVECTOR3(0.0f, 150.0f, -200.0f),	// Eye
						D3DXVECTOR3(0.0f, 0.0f, 0.0f),			// At
						D3DXVECTOR3(0.0f, 1.0f, 0.0f));			// Up

	// メッシュを初期化
	g_mesh = new Mesh();

	// ゲーム素材を初期化
	g_character = new Character();

	// ライトを初期化
	g_light = new Light(LT_PointLight);


	// レンダーステートパラメータの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートパラメータの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	return S_OK;
}

//*****************************************************************************
//
// 更新処理
//
//*****************************************************************************
void Updata(void)
{
	// 获取键盘消息并给予设置相应的 填充模式(塗りつぶしモード)
	if (GetAsyncKeyState(0x31) & 0x8000f)
	{
		// key 1,进行线框填充(ワイヤフレームを塗りつぶす)
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	if (GetAsyncKeyState(0x32) & 0x8000f)
	{
		// key 2,进行实体填充(面を塗りつぶす)
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	// 根据键盘消息设置相应的光照
	if (GetAsyncKeyState(0x51) & 0x8000f)         // key q
	{
		g_light->ChangeLight(LT_PointLight);
	}
	if (GetAsyncKeyState(0x57) & 0x8000f)         // key w
	{
		g_light->ChangeLight(LT_DirectionalLight);
	}
	if (GetAsyncKeyState(0x57) & 0x8000f)         // key e
	{
		g_light->ChangeLight(LT_SpotLight);
	}

	// カメラ注視点移動
	if (GetAsyncKeyState(0x33) & 0x8000f)
	{
		g_camera->At(1.0f, 'x');
	}
	if (GetAsyncKeyState(0x34) & 0x8000f)
	{
		g_camera->At(-1.0f, 'x');
	}

	// カメラ視点移動
	if (GetAsyncKeyState(0x35) & 0x8000f)
	{
		g_camera->Eye(1.0f, 'x');
	}
	if (GetAsyncKeyState(0x36) & 0x8000f)
	{
		g_camera->Eye(-1.0f, 'x');
	}

	if (GetAsyncKeyState(0x37) & 0x8000f)
	{
		g_camera->Eye(1.0f, 'z');
	}
	if (GetAsyncKeyState(0x38) & 0x8000f)
	{
		g_camera->Eye(-1.0f, 'z');
	}
}

//*****************************************************************************
//
// 描画処理
//
//*****************************************************************************
void Draw(HWND hwnd)
{
	// ビューイング変換
	g_camera->setViewMatrix();

	// プロジェクション変換
	g_camera->setProjMatrix();

	// キャラクターをワールド変換
	g_character->setWorldMatrix();

	
	// ビューポートを設定
	//g_camera->setViewport();

	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 1), 1.0f, 0);

	//定义一个矩形，用于获取主窗口矩形  
	//RECT formatRect;
	//GetClientRect(hwnd, &formatRect);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{

		//// レンダリングデフォルトモード
		//g_pD3DDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD); // 省略可

		// キャラクターを描画する
		g_character->GetMesh()->DrawModel();

		// キャラクターの座標インフォメーション
		g_character->PosToMessageAndMessageDraw(0);

		// カメラの座標インフォメーション
		g_camera->PosToMessageAndMessageDraw(1);

		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//*****************************************************************************
//
// 終了処理
//
//*****************************************************************************
void Release(void)
{
	// ポインタ
	SAFE_RELEASE_POINT(g_pD3D);
	SAFE_RELEASE_POINT(g_pD3DDevice);
	SAFE_RELEASE_POINT(g_pVertexBuffer);
	SAFE_RELEASE_POINT(g_pIndexBuffer);

	// クラスポインタ
	SAFE_RELEASE_CLASS_POINT(g_camera);
	SAFE_RELEASE_CLASS_POINT(g_mesh);
	SAFE_RELEASE_CLASS_POINT(g_light);
	SAFE_RELEASE_CLASS_POINT(g_character);
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

//*****************************************************************************
//
// 頂点バッファ取得関数
//
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 *GetVertexBuffer(void)
{
	return &g_pVertexBuffer;
}

//*****************************************************************************
//
// 頂点インデックスバッファ取得関数
//
//*****************************************************************************
LPDIRECT3DINDEXBUFFER9 *GetIndexBuffer(void)
{
	return &g_pIndexBuffer;
}


