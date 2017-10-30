//=============================================================================
//
// ゲーム資源処理クラス [GameObjects.h]
// Author : リョウ　カンシン
//
//=============================================================================
#ifndef _GAMEOBEJCTS_H_
#define _GAMEOBJECTS_H

#include "Main.h"

class GameObjects
{
private:
	bool m_Status;

	void InitEMVer(void);
	void InitEMLig(void);
public:
	GameObjects();					// コンストラクタ
	~GameObjects();					// デストラクタ

	void SetExample(ExampleType mode);
	bool GetStatus();

};

#endif // !_GAMEOBEJCTS_H_
