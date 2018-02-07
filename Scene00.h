//*****************************************************************************
//
// D3DTutorial���� [Scene00.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE00_H_
#define _SCENE00_H_

#include <map>

#include "ResourcesManager.h"
#include "Engine.h"
#include "Enemy.h"
#include "Bullet.h"

#include "Modules\Scene.h"
#include "Modules\Character.h"
#include "Modules\BoundingBox.h"
#include "Modules\Camera.h"
#include "Modules\Plane.h"
#include "Modules\Light.h"
#include "Modules\Shader.h"
#include "Modules\SkyBox.h"
#include "Modules\ScreenPolygon.h"

#include "Shader\RHWShader.h"
#include "Shader\CelShader.h"
#include "Shader\ShadowMapShader.h"

#define ENEMY_MAX 5
#define BULLET_MAX 21

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Scene00 : public Scene
{
private:
	Camera*			m_camera;		// �J����
	CelShader*		m_celShader;	// �g�D�\���V�F�[�_�[

	Shader*			m_shader;		// �x�[�V�b�N�V�F�[�_�[
	Plane*			m_sea;			// �t�B�[���h�C
	Character*		m_ship;			// �v���[���[
	Light*			m_directionLight;		// ���C�g
	Enemy*			m_enemyShip;	// �G
	Bullet*			m_bullet;		// �e
	SkyBox*			m_skyBox;		// �X�J�C�{�b�N�X

	ShadowMapShader*m_shadowMap;	// �V���h�[�}�b�v

	ScreenPolygon*	m_screenPolygon;// RHW�|���S��

public:
	Scene00();
	~Scene00();

	void Update();			// �X�V
	void Draw();			// �`��
	void Control();			// ����֐�
	void SetRenderState();	// �����_�����O��ݒ�

	bool CheckBB(Bullet* bullet, Enemy* enemy);		// �����蔻��
};

#endif // !_SCENE00_H_

