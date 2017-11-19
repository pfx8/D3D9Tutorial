//*****************************************************************************
//
// キャラクターベースクラス [CharacterClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_CLASS_H_
#define _CHARACTER_CLASS_H_

#include "Engine.h"

#include "MeshClass.h"
#include "MessageClass.h"
#include "BoundingBoxClass.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Character
{
private:
	// 固定属性
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小

	Mesh*			m_Mesh;			// メッシュ
	OutputMessage*	m_Message;		// Debugメッセージ
	BoundingBox*	m_BoundingBox;	// バウンディングボックス

	std::string		m_name;		// キャラクターの名前、これによってメッシュとテクスチャを探す

	float			m_Speed;		
public:
	Character();
	~Character();
	
	// 臨時ーーワールド変換
	void setWorldMatrix(D3DXMATRIX& mtxWorld);

	// 座標をメッセージに渡して、画面に描画する
	void PosToMessageAndMessageDraw(int row);

	// 座標を設定
	void InitCoordinate(D3DXVECTOR3 pos);

	// キャラクターの名前を決める
	void SetName(std::string name);

	// 名前でメッシュを作成
	void ChooseMesh(std::string name);

	// キャラクターの描画
	void Draw();

	// キャラクター移動
	void Move();

	// キャラクター更新
	void Update();

	// キャラクターのバウンディングボックスを取得
	BoundingBox* GetBoundingBox();

	// バウンディングボックス位置を取得
	D3DXVECTOR3* GetPosition();

	// 当たり判定
	bool CheckHitBB(Character* Object);
};


#endif // !_CHARACTER_CLASS_H_
