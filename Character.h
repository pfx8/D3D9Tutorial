//*****************************************************************************
//
// キャラクターベース処理 [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Engine.h"

#include "Mesh.h"
#include "DebugMessage.h"
#include "BoundingBox.h"

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
	DebugMessage*		m_Message;		// Debugメッセージ
	BoundingBox*		m_BoundingBox;	// バウンディングボックス

	std::string		m_name;			// キャラクターの名前、これによってメッシュとテクスチャを探す

	float			m_Speed;		
public:
	Character();
	~Character();

	// 座標を設定
	void SetCoordinate(D3DXVECTOR3 pos);
	// 臨時ーーワールド変換
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);
	// キャラクターの名前を決める
	void SetName(std::string name);

	// 座標をメッセージに渡して、画面に描画する
	void PosToMessageAndMessageDraw(int row);

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
	// メッシュを取得
	Mesh* GetMesh();

	// 当たり判定
	bool CheckHitBB(Character* Object);


};


#endif // !_CHARACTER_H_
