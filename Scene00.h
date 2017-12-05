//*****************************************************************************
//
// D3DTutorial処理 [Scene00.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE00_H_
#define _SCENE00_H_

#include "Engine.h"

#include <map>

#include "Scene.h"

#include "Character.h"
#include "Camera.h"
#include "Light.h"
#include "Plane.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	D3DXMATRIX		m_mtxWorld;	// ワールドマトリックス
	Camera*			m_camera;	// カメラ
	Light*			m_light;	// ライト

	Plane*			m_FieldStone;	// フィールド
	Character*		m_woman;		// 車, プレーヤー

public:
	Scene00();
	~Scene00();

	void Update();
	void Draw();

	void Scene00::UpdatePlayer(D3DXVECTOR3* Pos, D3DXVECTOR3* Speed);
};

#endif // !_SCENE00_H_

