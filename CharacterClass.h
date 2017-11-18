//*****************************************************************************
//
// キャラクターベースクラス [CharacterClass.h]
//
// Author : リョウ　カンシン
//
//*****************************************************************************
#ifndef _CHARACTER_CLASS_H_
#define _CHARACTER_CLASS_H_

#include "Main.h"

#include "MeshClass.h"
#include "TextureManagerClass.h"
#include "MessageClass.h"

class Character
{
private:
	// 固定属性
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小

	Mesh*			m_Mesh;		// メッシュ

	OutputMessage*	m_Message;	// Debugメッセージ

	std::string		m_name;		// キャラクターの名前、これによってメッシュとテクスチャを探す
public:
	Character();
	~Character();
	
	// 臨時ーーワールド変換
	void setWorldMatrix(D3DXMATRIX& mtxWorld);

	// キャラクターのメッシュの取得
	Mesh* GetMesh();

	// 座標をメッセージに渡して、画面に描画する
	void PosToMessageAndMessageDraw(int row);

	// 座標を設定
	void InitCoordinate(D3DXVECTOR3 pos);

	// キャラクターの名前を決める
	void SetName(std::string name);

	// 名前でメッシュを作成
	void ChooseMesh(std::string name);
};


#endif // !_CHARACTER_CLASS_H_
