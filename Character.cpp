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

	m_speed = D3DXVECTOR3(1.5f, 0.0f, 0.0f);

	// クラスポインタ
	m_mesh = new Mesh();
	m_message = new DebugMessage();
	m_boundingBox = new BoundingBox();
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Character::~Character()
{
	// クラスポインタ
	RELEASE_CLASS_POINT(m_mesh);
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);
}

//*****************************************************************************
//
// ワールド変換
//
//*****************************************************************************
void Character::SetWorldMatrix(D3DXMATRIX* mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスを初期化する
	D3DXMatrixIdentity(mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z); // カメラの方がもっと使う
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRot);

	// 平行移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTranslate);

	// ワールドマトリクスの初期化
	pDevice->SetTransform(D3DTS_WORLD, mtxWorld);
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	m_message->DrawPosMessage("Car1", m_pos, D3DXVECTOR2(0, float(row * 18 * 2)));
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
void Character::InitCharacter(D3DXVECTOR3 pos)
{
	// 位置
	m_pos = pos;

	// バウンディングボックスを初期化する
	m_boundingBox->InitBox(20, 30, 40, 0.4f);

	// DEBUG
}

//*****************************************************************************
//
// キャラクターの描画
//
//*****************************************************************************
void Character::Draw()
{
	//m_mesh->DrawModel();	// メッシュを描画する
	if (m_boundingBox->m_isBoundingBoxDraw == true)
	{
		m_boundingBox->Draw();	// バウンディングボックスを描画する
	}
}

//*****************************************************************************
//
// キャラクターの描画(Shader)
//
//*****************************************************************************
void Character::Draw(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl)
{
	
	//m_mesh->DrawModel(vertexShader, vertexDecl);// メッシュを描画する

	if (m_boundingBox->m_isBoundingBoxDraw == true)
	{
		m_boundingBox->Draw();	// バウンディングボックスを描画する
	}
}

//*****************************************************************************
//
// キャラクターの描画(Effect)
//
//*****************************************************************************
void Character::Draw(ID3DXEffect* effect)
{
	//m_mesh->DrawModel(effect);// メッシュを描画する

	if (m_boundingBox->m_isBoundingBoxDraw == true)
	{
		m_boundingBox->Draw();	// バウンディングボックスを描画する
	}
}

//*****************************************************************************
//
// キャラクター移動
//
//*****************************************************************************
void Character::Move()
{
	m_pos.x -= m_speed.x;
}

//*****************************************************************************
//
// キャラクター更新
//
//*****************************************************************************
void Character::Update(D3DXVECTOR3* pos, D3DXVECTOR3* speed, D3DXMATRIX* worldMatrix)
{
	// 操作更新
	if (GetKeyboardPress(DIK_A))	// key A
	{
		pos->x -= speed->x;
	}
	if (GetKeyboardPress(DIK_D))	// key D
	{
		pos->x += speed->x;
	}
	if (GetKeyboardPress(DIK_W))	// key W
	{
		pos->z += speed->x;
	}
	if (GetKeyboardPress(DIK_S))	// key S
	{
		pos->z -= speed->x;
	}

	if (GetKeyboardTrigger(DIK_Q))	// key Q
	{
		// バウンディングボックスをコントロール
		m_boundingBox->m_isBoundingBoxDraw = !m_boundingBox->m_isBoundingBoxDraw;
		std::cout << "[State] BoundingBox: " << std::boolalpha << m_boundingBox->m_isBoundingBoxDraw << std::endl;
	}
}

//*****************************************************************************
//
// 当たり判定
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3 ObjectPos = Object->m_pos;
	D3DXVECTOR3 ObjectSize = Object->m_boundingBox->m_size;

	if (
		m_pos.x + m_boundingBox->m_size.x / 2 > ObjectPos.x - ObjectSize.x / 2 &&
		m_pos.x - m_boundingBox->m_size.x / 2 < ObjectPos.x + ObjectSize.x / 2 &&
		m_pos.y - m_boundingBox->m_size.y / 2 < ObjectPos.y + ObjectSize.y / 2 &&
		m_pos.y + m_boundingBox->m_size.y / 2 > ObjectPos.y - ObjectSize.y / 2 &&
		m_pos.z + m_boundingBox->m_size.z / 2 > ObjectPos.z - ObjectSize.z / 2 &&
		m_pos.z - m_boundingBox->m_size.z / 2 < ObjectPos.z + ObjectSize.z / 2
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}