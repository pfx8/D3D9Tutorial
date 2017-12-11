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
	DebugMessage*	m_message;		// Debugメッセージ
	std::string		m_name;			// キャラクターの名前、これによってメッシュとテクスチャを探す

public:
	// 固定属性
	D3DXVECTOR3		m_pos;		// 位置
	D3DXVECTOR3		m_speed;		// スピード
	D3DXVECTOR3		m_rot;		// 回転
	D3DXVECTOR3		m_scl;		// 拡大縮小
	Mesh*			m_mesh;		// メッシュ
	BoundingBox*		m_boundingBox;	// バウンディングボックス

	Character();
	~Character();

	void InitCharacter(D3DXVECTOR3 pos);	// 座標を設定
	void SetWorldMatrix(D3DXMATRIX* mtxWorld);		// 臨時ーーワールド変換

	void SetName(std::string name) { m_name = name; };
	std::string GetName() { return m_name; };

	void PosToMessageAndMessageDraw(int row);	// 座標をメッセージに渡して、画面に描画する
	void Draw();	// キャラクターの描画
	void Draw(ID3DXEffect* effect);	// キャラクターの描画(Effect)
	void Draw(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl);	// キャラクターの描画(Shader)
	void Move();	//  臨時ーーキャラクター移動
	
	void Update(D3DXVECTOR3* pos, D3DXVECTOR3* speed, D3DXMATRIX* worldMatrix);	// キャラクター更新
	bool CheckHitBB(Character* Object);	// 当たり判定

};
#endif // !_CHARACTER_H_

