//*****************************************************************************
//
// �V�[��01���� [Scene01.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE01_H_
#define _SCENE01_H_

#include "Engine.h"

#include <map>

#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Shader.h"


//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene01 : public Scene
{
private:
	D3DXMATRIX		m_mtxWorld;	// ���[���h�}�g���b�N�X

	Camera*			m_camera;	// �J����
	Light*			m_light;	// ���C�g

	ID3DXMesh*		m_teapot;	// �e�B�[�|�b�g
	ID3DXMesh*		m_box;
	Shader*			m_shader;	// �V�F�[�_�[
public:
	Scene01();
	~Scene01();

	void Update();
	void Draw();
};

#endif // !_SCENE01_H_
