//*****************************************************************************
//
// キャラクターベース処理 [Character.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "Character.h"

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

	m_Speed = 1.5f;

	// クラスポインタ
	m_Mesh = new Mesh();
	m_Message = new DebugMessage();
	m_BoundingBox = new BoundingBox();
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
	SAFE_RELEASE_CLASS_POINT(m_BoundingBox);
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Character::SetWorldMatrix(D3DXMATRIX& mtxWorld)
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
void Character::SetCoordinate(D3DXVECTOR3 pos)
{
	m_pos = pos;

	// バウンディングボックスを初期化する
	m_BoundingBox->InitBox(20, 30, 40, 0.4f);
	
	// DEBUG
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

//*****************************************************************************
//
// キャラクターの描画
//
//*****************************************************************************
void Character::Draw()
{
	// メッシュを描画する
	m_Mesh->DrawModel();

	// バウンディングボックスを描画する
	m_BoundingBox->Draw();
}

//*****************************************************************************
//
// キャラクター移動
//
//*****************************************************************************
void Character::Move()
{
	m_pos.x -= m_Speed;
}

//*****************************************************************************
//
// キャラクター更新
//
//*****************************************************************************
void Character::Update()
{
	if (GetKeyboardPress(DIK_A))			// key A
	{
		m_pos.x -= m_Speed;
	}
	if (GetKeyboardPress(DIK_D))			// key D
	{
		m_pos.x += m_Speed;
	}
	if (GetKeyboardPress(DIK_W))			// key W
	{
		m_pos.z += m_Speed;
	}
	if (GetKeyboardPress(DIK_S))			// key S
	{
		m_pos.z -= m_Speed;
	}
}

//*****************************************************************************
//
// キャラクターのバウンディングボックスを取得
//
//*****************************************************************************
BoundingBox* Character::GetBoundingBox()
{
	return m_BoundingBox;
}

//*****************************************************************************
//
// バウンディングボックス位置を取得
//
//*****************************************************************************
D3DXVECTOR3* Character::GetPosition()
{
	return &m_pos;
}

//*****************************************************************************
//
// 当たり判定
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3* ObjectPos = Object->GetPosition();
	D3DXVECTOR3* ObjectSize = Object->GetBoundingBox()->GetSize();

	if (
		GetPosition()->x + GetBoundingBox()->GetSize()->x / 2 > ObjectPos->x - ObjectSize->x / 2 &&
		GetPosition()->x - GetBoundingBox()->GetSize()->x / 2 < ObjectPos->x + ObjectSize->x / 2 &&
		GetPosition()->y - GetBoundingBox()->GetSize()->y / 2 < ObjectPos->y + ObjectSize->y / 2 &&
		GetPosition()->y + GetBoundingBox()->GetSize()->y / 2 > ObjectPos->y - ObjectSize->y / 2 &&
		GetPosition()->z + GetBoundingBox()->GetSize()->z / 2 > ObjectPos->z - ObjectSize->z / 2 &&
		GetPosition()->z - GetBoundingBox()->GetSize()->z / 2 < ObjectPos->z + ObjectSize->z / 2
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//*****************************************************************************
//
// メッシュを取得
//
//*****************************************************************************
Mesh* Character::GetMesh()
{
	return m_Mesh;
}