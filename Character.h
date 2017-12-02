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
	DebugMessage*		m_message;		// Debugメッセージ
	BoundingBox*		m_boundingBox;	// バウンディングボックス

	std::string		m_name;			// キャラクターの名前、これによってメッシュとテクスチャを探す
	
	std::map<std::string, void*> m_memberList;// プライベートメンバーリスト
	void InitMemberList();// プライベートメンバーリスト初期化
public:
	// 固定属性
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_speed;		// スピード
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小

	Mesh*			m_meshPoint;		// メッシュ
	Character();
	~Character();

	bool		m_BoundingBoxON;	// バウンディングボックスを描画する

	void InitCharacter(D3DXVECTOR3 pos);	// 座標を設定
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);		// 臨時ーーワールド変換

	void SetName(std::string name) { m_name = name; };
	std::string GetName() { return m_name; };

	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する
	void Draw();	// キャラクターの描画
	void Draw(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl);	// キャラクターの描画(Shader)
	void Move();	//  臨時ーーキャラクター移動
	
	void Update();	// キャラクター更新
	Mesh* GetMesh();	// メッシュを取得
	bool CheckHitBB(Character* Object);	// 当たり判定

	// 取得
	BoundingBox* GetBoundingBox();	// キャラクターのバウンディングボックスを取得
	D3DXVECTOR3* GetPosition();		// キャラクター位置を取得

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
		if (m_memberList.find(MemberName) != m_memberList.end())
		{
			return m_memberList[MemberName];
		}
	};
};

#endif // !_CHARACTER_H_

