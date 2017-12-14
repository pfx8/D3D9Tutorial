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
// �N���X�錾
//
//*****************************************************************************
class Scene02 : public Scene
{
private:
	D3DXMATRIX	m_mtxWorld;	// ���[���h�}�g���b�N�X
	Camera*		m_camera;		// �J����
	Shader*		m_shader;		// �V�F�[�_�[
	Plane*		m_plane;		// ����1

	LPDIRECT3DTEXTURE9 m_plane2;	// ����2
public:
	Scene02();
	~Scene02();

	void Update();
	void Draw();
};

#endif // !_SCENE01_H_

