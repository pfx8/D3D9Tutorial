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
	// クラスポインタ
	this->message = new DebugMessage;
	this->check = new BoundingBox;
	this->space = new BoundingBox;
	this->player.shipBody = new Model;
	this->player.shipCannon = new Model;

	InitCharacter();
}

//*****************************************************************************
//
// 初期化
//
//*****************************************************************************
void Character::InitCharacter()
{
	this->upVector = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->lookVector = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	this->rightVector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	this->pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	this->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	this->waveAngle = 0.0f;
	this->speed = 0.0f;

	this->HP = MAX_HP;

	this->leftTime = 3.0f;
	this->leftShooting = false;
	this->rightTime = 3.0f;
	this->rightShooting = false;

	this->leverLevel = LL_STOP;
}

//*****************************************************************************
//
// デストラクタ
//
//*****************************************************************************
Character::~Character()
{
	RELEASE_CLASS_POINT(this->message);
	RELEASE_CLASS_POINT(this->check);
	RELEASE_CLASS_POINT(this->space);

	RELEASE_CLASS_ARRY_POINT(this->player.shipBody);
	RELEASE_CLASS_ARRY_POINT(this->player.shipCannon);
}

//*****************************************************************************
//
// 座標をメッセージに渡して、画面に描画する
//
//*****************************************************************************
void Character::PosToMessageAndMessageDraw(int row)
{
	D3DXVECTOR3 temp;
	temp.x = lightMatrix._41;
	temp.y = lightMatrix._42;
	temp.z = lightMatrix._43;
	
	D3DXVECTOR3 temp2;
	temp2.x = leftTime;
	temp2.y = rightTime;
	temp2.z = D3DXToDegree(rot.y);

	//this->message->DrawPosMessage("Light", temp, D3DXVECTOR2(0, float((row + 0) * 18)));
	this->message->DrawPosMessage("time", temp2, D3DXVECTOR2(0, float((row + 0) * 18)));
}

//*****************************************************************************
//
// キャラクターの描画
//
//*****************************************************************************
void Character::Draw(CelShader* celShader, D3DXMATRIX* VPMatrix)
{
	// メッシュを描画する
	this->player.shipBody->DrawModel(celShader, &this->worldMatrix, VPMatrix, &lightMatrix, MT_ship);
	this->player.shipCannon->DrawModel(celShader, &this->worldMatrix, VPMatrix, &lightMatrix, MT_ship);
}

//*****************************************************************************
//
// キャラクター更新
//
//*****************************************************************************
void Character::Update(float rot)
{
	// プレーヤー操作 
	if (GetKeyboardTrigger(DIK_W))	// 前に進む
	{
		if (this->leverLevel == LL_STOP)
		{
			this->ChangeLever(LL_FRONT);
		}
		else
		{
			this->ChangeLever(LL_STOP);
		}	
	}
	if (GetKeyboardTrigger(DIK_S))	// 後ろに進む
	{
		if (this->leverLevel == LL_STOP)
		{
			this->ChangeLever(LL_BACK);
		}
		else
		{
			this->ChangeLever(LL_STOP);
		}
	}

	if (GetKeyboardPress(DIK_A))	// 左回転
	{
		// 更新キャラクターをカメラの回転角度0.05
		this->RotationVecUp(-0.5f / 180.0f * D3DX_PI);
	}
	else if (GetKeyboardPress(DIK_D))	// 右回転
	{
		// 更新キャラクターをカメラの回転角度
		this->RotationVecUp(0.5f / 180.0f * D3DX_PI);
	}

	// テスト、HP減り
	if (GetKeyboardTrigger(DIK_P))
	{
		this->HP -= 1;
	}

	// 波に合わせて揺れる
	this->waveAngle = rot;
	if (this->waveAngle > D3DX_PI * 2.0f)
		this->waveAngle = 0.0f;
	this->pos.y = 0.5 + 0.8 * sinf(this->waveAngle);

	// 移動
	switch (leverLevel)
	{
	case LL_FRONT:
		this->speed += 0.0003f;
		if (this->speed >= MAX_FRONT_SPEED_COEFFICIENT)
			this->speed = MAX_FRONT_SPEED_COEFFICIENT;
		break;
	case LL_STOP:
		if (this->speed > 0)
		{
			this->speed -= 0.0001f;
			if (this->speed <= 0)
				this->speed = 0;
		}
		else if (this->speed < 0)
		{
			this->speed += 0.0003f;
			if (this->speed >= 0)
				this->speed = 0;
		}
		else
		{
			this->speed = 0.0f;
		}
		break;
	case LL_BACK:
		this->speed -= 0.0001f;
		if (this->speed <= MAX_BACK_SPEED_COEFFICIENT)
			this->speed = MAX_BACK_SPEED_COEFFICIENT;
		break;
	default:
		break;
	}

	// 移動
	MoveAlongVecLook(this->speed);

	// ワールド変換
	SetWorldMatrix();

	// 発射更新
	if (this->leftShooting == true)
	{
		leftTime -= 3.0f / 180.0f;
		if (leftTime <= 0)
		{
			leftTime = 3;
			leftShooting = false;
		}
	}

	if (this->rightShooting == true)
	{
		rightTime -= 3.0f / 180.0f;
		if (rightTime <= 0)
		{
			rightTime = 3;
			rightShooting = false;
		}
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
	this->rot.y += angle;

	if (this->rot.y >= D3DXToRadian(360.0f))
	{
		this->rot.y = 0.0f;
	}
	if (this->rot.y <= D3DXToRadian(-360.0f))
	{
		this->rot.y = 0.0f;
	}

	D3DXMATRIX rotMatrix;
	D3DXMatrixRotationAxis(&rotMatrix, &this->upVector, angle);					// 回転行列を作る
	D3DXVec3TransformCoord(&this->lookVector, &this->lookVector, &rotMatrix);	// カメラの新しい座標を計算する

	D3DXVec3Normalize(&this->lookVector, &this->lookVector);
	D3DXVec3Cross(&this->rightVector, &this->lookVector, &this->upVector);
	D3DXVec3Normalize(&this->rightVector, &this->rightVector);
	D3DXVec3Cross(&this->upVector, &this->rightVector, &this->lookVector);
	D3DXVec3Normalize(&this->upVector, &this->upVector);

}

//*****************************************************************************
//
// レバーの操作によってスピードを変わる
//
//*****************************************************************************
void Character::ChangeLever(LEVER_LEVEL level)
{
	this->leverLevel = level;

	// コンソールに出すメッセージ
	switch (leverLevel)
	{
	case LL_FRONT:
		std::cout << "前" << std::endl; break;
	case LL_STOP:
		std::cout << "停" << std::endl; break;
	case LL_BACK:
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
D3DXVECTOR3 Character::MoveAlongVecLook(float speedCoefficient)
{
	this->pos += this->lookVector * speedCoefficient;

	return this->lookVector * speedCoefficient;
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
	D3DXMatrixIdentity(&this->worldMatrix);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, this->scl.x, this->scl.y, this->scl.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&this->lightMatrix, this->rot.y, this->rot.x, this->rot.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &this->lightMatrix);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->worldMatrix, &this->worldMatrix, &mtxTranslate);

	// ライトマトリックス
	D3DXMatrixTranslation(&mtxTranslate, 0, this->pos.y, 0);
	D3DXMatrixMultiply(&this->lightMatrix, &this->lightMatrix, &mtxTranslate);
}

//*****************************************************************************
//
// 当たり判定
//
//*****************************************************************************
bool Character::CheckHitBB(Character* Object)
{
	D3DXVECTOR3 ObjectPos = Object->pos;
	D3DXVECTOR3 ObjectSize = Object->check->size;

	if (
		this->pos.x + this->check->size.x / 2 > ObjectPos.x - ObjectSize.x / 2 &&
		this->pos.x - this->check->size.x / 2 < ObjectPos.x + ObjectSize.x / 2 &&
		this->pos.y - this->check->size.y / 2 < ObjectPos.y + ObjectSize.y / 2 &&
		this->pos.y + this->check->size.y / 2 > ObjectPos.y - ObjectSize.y / 2 &&
		this->pos.z + this->check->size.z / 2 > ObjectPos.z - ObjectSize.z / 2 &&
		this->pos.z - this->check->size.z / 2 < ObjectPos.z + ObjectSize.z / 2
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}