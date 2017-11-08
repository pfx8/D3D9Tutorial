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
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_rot;
	D3DXVECTOR3		m_scl;

	Mesh*			m_Mesh;

	OutputMessage*	m_Message;
public:
	Character();
	~Character();
	
	// 臨時ーーワールド変換
	void setWorldMatrix();

	// キャラクターのメッシュの取得
	Mesh* GetMesh();

	// 座標をメッセージに渡して、画面に描画する
	void PosToMessageAndMessageDraw(int row);
};


#endif // !_CHARACTER_CLASS_H_
