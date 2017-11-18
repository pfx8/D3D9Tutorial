//*****************************************************************************
//
// キャラクターベースクラス [CharacterClass.cpp]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#include "CharacterClass.h"

//*****************************************************************************
//
// コンストラクタ
//
//*****************************************************************************
Character::Character()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	
	m_name = " ";

	// クラスポインタ
	m_Mesh = new Mesh();
	m_Message = new OutputMessage();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Character::~Character()
{
	// クラスポインタ
	SAFE_RELEASE_CLASS_POINT(m_Mesh);
	SAFE_RELEASE_CLASS_POINT(m_Message);
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Character::setWorldMatrix(D3DXMATRIX& mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); // カメラの方がもっと使う
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリクスの初期化
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
}

//*****************************************************************************
//
// キャラクターのメッシュの取得
//
//*****************************************************************************
Mesh* Character::GetMesh()
{
	return m_Mesh;
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	m_Message->DrawPosMessage("Car1", m_pos, D3DXVECTOR2(0, float(row * 18 * 2)));
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
void Character::InitCoordinate(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//*****************************************************************************
//
// キャラクターの名前を決める
//
//*****************************************************************************
void Character::SetName(std::string name)
{
	m_name = name;

	// 名前でメッシュとテクスチャを読み込み
	ChooseMesh(m_name);
}

//*****************************************************************************
//
// 名前でメッシュを作成
//
//*****************************************************************************
void Character::ChooseMesh(std::string name)
{
	m_Mesh->SetMesh(name);
}