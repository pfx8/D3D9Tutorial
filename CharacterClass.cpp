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

	m_Mesh	= new Mesh();
	m_Mesh->ReadXFile();

	m_Message = new OutputMessage();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Character::~Character()
{
	SAFE_RELEASE_CLASS_POINT(m_Mesh);
	SAFE_RELEASE_CLASS_POINT(m_Message);
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Character::setWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate, mtxWorld;

	// ワールドマトリックスの初期化
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
	m_Message->DrawPosMessage("Car1", m_pos, D3DXVECTOR2(0, row * 18 * 2));
}