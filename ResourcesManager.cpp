//*****************************************************************************
//
// リソース管理クラス [ResourcesManager.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "ResourcesManager.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
ResourcesManager::ResourcesManager()
{
	// テクスチャ検索マッピングを作る
	m_textureList["back"] = "data/TEXTURE/skybox/back.jpg";
	m_textureList["front"] = "data/TEXTURE/skybox/front.jpg";
	m_textureList["left"] = "data/TEXTURE/skybox/left.jpg";
	m_textureList["right"] = "data/TEXTURE/skybox/right.jpg";
	m_textureList["top"] = "data/TEXTURE/skybox/top.jpg";
	m_textureList["skybox"] = "data/TEXTURE/skybox.png";
	m_textureList["fieldTransparent"] = "data/TEXTURE/field003.png";
	m_textureList["fieldSea"] = "data/TEXTURE/sea3k.png";
	m_textureList["fieldSea2"] = "data/TEXTURE/sea3k2.png";
	m_textureList["title"] = "data/TEXTURE/TitleName.png";
	m_textureList["press"] = "data/TEXTURE/Presskey.png";
	m_textureList["tex"] = "data/TEXTURE/shipdiffuse.png";
	m_textureList["NULL"] = "NULL";

	// メッシュ検索マッピングを作る
	m_meshList["car1"] = "data/MODEL/car001.x";
	m_meshList["car2"] = "data/MODEL/car002.x";
	m_meshList["woman"] = "data/MODEL/woman.x";
	m_meshList["rockman"] = "data/MODEL/rockman.x";
	m_meshList["ship"] = "data/MODEL/ship.x";
	m_meshList["ship2"] = "data/MODEL/ship2.x";
	m_meshList["ball"] = "data/MODEL/ball.x";
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
ResourcesManager::~ResourcesManager()
{

}

//*****************************************************************************
//
// テクスチャを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetTextureStruct(name).data() != "NULL")
	{
		// テクスチャを読み込み
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice, 
			//GetTextureStruct(name).data(),
			GetTextureStruct(name).c_str(),
			texturePoint)))
		{
			std::cout << "[Error] Loading Texture<" << name << "> Failed!" << std::endl;	// コンソールにメッセージを出す
			return E_FAIL;
		}
		else
		{
			std::cout << "[Information] Loading Texture<" << name << "> Success!" << std::endl;	// コンソールにメッセージを出す
			return S_OK;
		}
	}
	else
	{
		*texturePoint = NULL;
		return S_OK;
	}
}


//*****************************************************************************
//
// テクスチャ構造体を取得
//
//*****************************************************************************
std::string ResourcesManager::GetTextureStruct(std::string name)
{
	if(m_textureList.find(name) != m_textureList.end())
	{
		return m_textureList[name];
	}
}

//*****************************************************************************
//
// メッシュを読み込み
//
//*****************************************************************************
HRESULT ResourcesManager::LoadMesh(std::string name, Model* model)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (GetMeshPath(name).c_str() != "NULL")
	{
		if (FAILED(D3DXLoadMeshFromX(			// Xファイルの読み込み
			GetMeshPath(name).c_str(),			// モデルのファイル名
			D3DXMESH_SYSTEMMEM,					// メッシュのメモリ確保オプション
			pDevice,							// デバイスへのポインタ
			NULL,								// 隣接性データを含むバッファへのポインタ
			&model->m_material->m_materialBuffer,// マテリアルデータを含むバッファへのポインタ
			NULL,								// エフェクトインスタンスを含むバッファへのポインタ
			&model->m_material->m_materialNum,	// マテリアル構造体の数
			&model->m_meshPoint)))				// メッシュへのポインタ
		{
			std::cout << "[Error] Loading Model<" << name << "> Failed!" << std::endl;
			return E_FAIL;
		}
		else
		{
			std::cout << "[Information] Loading Model<" << name << "> Success!" << std::endl;
		}
	}

	model->m_material->m_materialPoint = new D3DMATERIAL9[model->m_material->m_materialNum];	// マテリアルの数によってマテリアルを格納できるメモリを確保
	model->m_meshTexturePoint = new LPDIRECT3DTEXTURE9[model->m_material->m_materialNum];		// マテリアルの数によってテクスチャを格納できるメモリを確保

	D3DXMATERIAL* materials = (D3DXMATERIAL*)model->m_material->m_materialBuffer->GetBufferPointer();	// Xファイルに保存されているマテリアル情報構造体
	for (DWORD count = 0; count < model->m_material->m_materialNum; count++)
	{
		model->m_material->m_materialPoint[count] = materials[count].MatD3D; // マテリアルのプロパティをコピー
		model->m_material->m_materialPoint[count].Ambient = model->m_material->m_materialPoint[count].Diffuse;	// アンビエント色をディフューズ色にする

		// Xファイルの情報によってすべてのテクスチャを読み込み
		if (materials[count].pTextureFilename == NULL)
		{
			model->m_meshTexturePoint[count] = NULL;	// テクスチャ無し
		}
		else
		{
			model->m_meshTexturePoint[count] = NULL;

			if (FAILED(D3DXCreateTextureFromFile(pDevice, materials[count].pTextureFilename, &model->m_meshTexturePoint[count])))
			{
				std::cout << "[Error] Material's texture load Fail!" << std::endl;
				return E_FAIL;
			}
		}
	}

	// ッシュの面および頂点の順番変更を制御し、パフォーマンスを最適化する
	model->m_meshPoint->OptimizeInplace(D3DXMESHOPT_ATTRSORT, NULL, NULL, NULL, NULL);

	return S_OK;
}

//*****************************************************************************
//
// メッシュパスを取得
//
//*****************************************************************************
std::string ResourcesManager::GetMeshPath(std::string name)
{
	if (m_meshList.find(name) != m_meshList.end())
	{
		return m_meshList[name];
	}

	return NULL;
}