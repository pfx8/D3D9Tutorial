//*****************************************************************************
//
// シーン処理 [Scene.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Scene.h"

#include "fstream"

using namespace std;

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Scene::Scene()
{	
	m_resourcesManager = new ResourcesManager;	// リソース
	m_message = new DebugMessage;
	D3DXMatrixIdentity(&m_worldMatrix);	// ワールドマトリックスを初期化する

	// テクスチャを読み込み
	// m_resourcesManager->InitTexture();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Scene::~Scene()
{
	// クラスポインタ
	// リソース
	RELEASE_CLASS_POINT(m_resourcesManager);
	RELEASE_CLASS_POINT(m_message);
}

//*****************************************************************************
//
// ファイル(blender)からシンーの資源を読み込み
//
//*****************************************************************************
//HRESULT Scene::LoadSceneFile(string name)
//{
//	// コンソールにメッセージを出す
//	cout << "Loading " << name << endl;
//
//	// 読み込みオブジェクトを作る
//	ifstream fin;
//	
//	// ファイルを読み込み
//	fin.open(name);
//
//	// 読み込みは失敗した場合
//	if (fin.fail())
//	{
//		// コンソールにメッセージを出す
//		cout << "エラー[ 読み込み失敗 ]" << endl;
//		return E_FAIL;
//	}
//	else
//	{
//		// コンソールにメッセージを出す
//		cout << name << " ok!" << endl;
//		char PathTemp[100];
//		while (!fin.eof())
//		{
//			fin.getline(PathTemp, 100);
//			cout << PathTemp << endl;
//		}
//
//		// 未完成
//	}
//
//	return S_OK;
//}