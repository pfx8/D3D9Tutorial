//*****************************************************************************
//
// PixelShader [Scene02.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE02_H_
#define _SCENE02_H_

#include "Engine.h"
#include "Shader.h"

#include <map>

#include "Modules/Scene.h"
#include "Modules/Camera.h"
#include "Modules/Plane.h"

//*****************************************************************************
//
// クラス宣言
//
//*****************************************************************************
class Scene02 : public Scene
{
private:
	D3DXMATRIX	m_mtxWorld;	// ワールドマトリックス
	Camera*		m_camera;		// カメラ
	Shader*		m_shader;		// シェーダー
	Plane*		m_plane;		// 平面1

	LPDIRECT3DTEXTURE9 m_plane2;	// 平面2
public:
	Scene02();
	~Scene02();

	void Update();
	void Draw();
};

#endif // !_SCENE01_H_

