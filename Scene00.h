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
#include "Shader\CelShader.h"

#define ENEMY_MAX 1
#define BULLET_MAX 10

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
	Plane*			m_fieldStone;	// �t�B�[���h
	Character*		m_ship;			// �v���[���[
	Light*			m_light;		// ���C�g
	Enemy*			m_enemyShip;	// �G
	Bullet*			m_bullet;		// �e
	//SkyBox*			m_skyBox;		// �X�J�C�{�b�N�X

	bool			m_isGameStart;
public:
	Scene00();
	~Scene00();

	void Update();			// �X�V
	void Draw();				// �`��
	void Control();			// ����֐�
	void SetRenderState();	// �����_�����O��ݒ�

	bool CheckBB(Bullet* bullet, Enemy* enemy);		// �����蔻��
};

#endif // !_SCENE00_H_

