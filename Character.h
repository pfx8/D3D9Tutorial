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

#include <map>

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
	D3DXVECTOR3		m_Speed;		// スピード
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小

	Mesh*			m_Mesh;			// メッシュ
	DebugMessage*		m_Message;		// Debugメッセージ
	BoundingBox*		m_BoundingBox;	// バウンディングボックス

	std::string		m_name;			// キャラクターの名前、これによってメッシュとテクスチャを探す
	
	std::map<std::string, void*> m_MemberList;// プライベートメンバーリスト
	void InitMemberList();// プライベートメンバーリスト初期化
public:
	Character();
	~Character();

	bool		m_BoundingBoxON;	// バウンディングボックスを描画する

	// 座標を設定
	void InitCharacter(D3DXVECTOR3 pos, PDIRECT3DTEXTURE9* texturePoint, std::string meshPath);
	// 臨時ーーワールド変換
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);

	// 座標をメッセージに渡して、画面に描画する
	void PosToMessageAndMessageDraw(int row);

	// キャラクターの描画
	void Draw();

	//  臨時ーーキャラクター移動
	void Move();

	// キャラクター更新
	void Update();
	// メッシュを取得
	Mesh* GetMesh();

	// 当たり判定
	bool CheckHitBB(Character* Object);

	// 取得
	// キャラクターのバウンディングボックスを取得
	BoundingBox* GetBoundingBox();
	// キャラクター位置を取得
	D3DXVECTOR3* GetPosition();


	//*****************************************************************************
	//
	// プライベートメンバーを取得
	//
	//*****************************************************************************
	/*template <typename T> T* GetMember(std::string MemberName)
	{
		if (m_MemberList.find(MemberName) != m_MemberList.end())
		{
			return dynamic_cast<T*> m_MemberList[MemberName];
		}
	};*/

	/*auto* GetMember(std::string MemberName)
	{
		if (m_MemberList->find(MemberName) != m_MemberList->end())
		{
			return m_MemberList->at(MemberName);
		}
	};*/

	auto* GetMember(std::string MemberName)
	{
		if (m_MemberList.find(MemberName) != m_MemberList.end())
		{
			return m_MemberList[MemberName];
		}
	};
};

#endif // !_CHARACTER_H_

