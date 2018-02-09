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
	m_upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_lookVector = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	m_rightVector = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_waveAngle = 0.0f;
	m_speedCoefficient = 0.0f;
	m_leverLevel = 0;

	// クラスポインタ
	m_message = new DebugMessage;
	m_boundingBox = new BoundingBox;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Character::~Character()
{
	RELEASE_CLASS_POINT(m_message);
	RELEASE_CLASS_POINT(m_boundingBox);

	RELEASE_CLASS_ARRY_POINT(m_model);
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	m_message->DrawPosMessage("Pos", m_pos, D3DXVECTOR2(0, float((row + 0) * 18)));
}

//*****************************************************************************
//
// 座標を設定
//
//*****************************************************************************
void Character::InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction, int modelNum)
{
	m_pos = pos;	// 位置
	
	m_modelNum = modelNum;
	m_model = new Model[m_modelNum]; // モデルを数によって初期化
}

//*****************************************************************************
//
// キャラクターの描画
//
//*****************************************************************************
void Character::Draw(CelShader* celShader)
{
	m_model->DrawModel(celShader);	// メッシュを描画する
}

//*****************************************************************************
//
// キャラクター更新
//
//*****************************************************************************
void Character::Update(float rot)
{
	// 波
	m_waveAngle = rot;
	if (m_waveAngle > D3DX_PI * 2.0f)
		m_waveAngle = 0.0f;
	m_pos.y = 0.8 * sinf(m_waveAngle);

	// 移動
	switch (m_leverLevel)
	{
	case LL_BACK:
		m_speedCoefficient -= 0.0001f;
		if (m_speedCoefficient <= MAX_BACK_COEFFICIENT)
			m_speedCoefficient = MAX_BACK_COEFFICIENT;
		break;
	case LL_STOP:
		m_speedCoefficient = 0.0f;
		break;
	case LL_FRONT:
		m_speedCoefficient += 0.0001f;
		if (m_speedCoefficient >= MAX_FRONT_COEFFICIENT)
			m_speedCoefficient = MAX_FRONT_COEFFICIENT;
		break;
	default:
		break;
	}
	MoveAlongVecLook(m_speedCoefficient);
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

//*****************************************************************************
//
// 上方向のベクトルにして回転
//
//*****************************************************************************
void Character::RotationVecUp(float angle)
{
	// 角度を記録する
	m_rot.y += angle;

	if (m_rot.y > D3DX_PI / 6.0f)
	{
		m_rot.y = D3DX_PI / 6.0f;
	}
	if (m_rot.y < -D3DX_PI / 6.0f)
	{
		m_rot.y = -D3DX_PI / 6.0f;
	}

	// 新しい右方向ベクトルを計算する
	m_rightVector.x = cosf(m_rot.y + D3DX_PI / 2);
	m_rightVector.z = sinf(m_rot.y + D3DX_PI / 2);

	// 新しい注視方向ベクトルを計算する
	m_lookVector.x = cosf(m_rot.y);
	m_lookVector.z = sinf(m_rot.y);
}

//*****************************************************************************
//
// レバーの操作によってスピードを変わる
//
//*****************************************************************************
void Character::ChangeLever(LEVER_LEVEL scalars)
{
	switch (m_leverLevel)
	{
	case LL_BACK:
		if (scalars == LL_STOP)
		{
			m_leverLevel = LL_STOP;
			m_speedCoefficient += 0.0001f;
			if (m_speedCoefficient >= 0.0f)
				m_speedCoefficient = 0.0f;
		}
		if (scalars == LL_FRONT)
		{
			m_leverLevel = LL_FRONT;
			m_speedCoefficient += 0.0001f;
			if (m_speedCoefficient >= MAX_FRONT_COEFFICIENT)
				m_speedCoefficient = MAX_FRONT_COEFFICIENT;
		}
		break;
	case LL_STOP:
		if (scalars == LL_BACK)
		{
			m_leverLevel = LL_BACK;
			m_speedCoefficient -= 0.0001f;
			if (m_speedCoefficient <= MAX_BACK_COEFFICIENT)
				m_speedCoefficient = MAX_BACK_COEFFICIENT;
		}
		if (scalars == LL_FRONT)
		{
			m_leverLevel = LL_FRONT;
			m_speedCoefficient += 0.0001f;
			if (m_speedCoefficient >= MAX_FRONT_COEFFICIENT)
				m_speedCoefficient = MAX_FRONT_COEFFICIENT;
		}
		break;
	case LL_FRONT:
		if (scalars == LL_BACK)
		{
			m_leverLevel = LL_BACK;
			m_speedCoefficient -= 0.0001f;
			if (m_speedCoefficient <= MAX_BACK_COEFFICIENT)
				m_speedCoefficient = MAX_BACK_COEFFICIENT;
		}
		if (scalars == LL_STOP)
		{
			m_leverLevel = LL_STOP;
			m_speedCoefficient -= 0.0001f;
			if (m_speedCoefficient <= 0.0f)
				m_speedCoefficient = 0.0f;
		}
		break;
	default:
		break;
	}

	// test
	switch (m_leverLevel)
	{
	case LL_BACK:
		std::cout << "前" << std::endl; break;
	case LL_STOP:
		std::cout << "停" << std::endl; break;
	case LL_FRONT:
		std::cout << "後" << std::endl; break;
	default:
		break;
	}

}

//*****************************************************************************
//
// 注視方向に沿って移動
//
//*****************************************************************************
D3DXVECTOR3 Character::MoveAlongVecLook(float unit)
{
	m_pos += m_lookVector * unit;

	return m_lookVector * unit;
}

//*****************************************************************************
//
// ワールド変換を設定
//
//*****************************************************************************
void Character::SetWorldMatrix()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxScl, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&this->m_rotMatrix, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &this->m_rotMatrix);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_worldMatrix, &m_worldMatrix, &mtxTranslate);

	// ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_worldMatrix);
}

//*****************************************************************************
//
// 回転マトリックスを取得
//
//*****************************************************************************
D3DXMATRIX Character::GetRotMatrix()
{
	return this->m_rotMatrix;
}