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
	Camera*				camera;		// �J����
	CelShader*			celShader;	// �g�D�\���V�F�[�_�[

	Shader*				shader;		// �x�[�V�b�N�V�F�[�_�[
	Plane*				sea;			// �t�B�[���h�C
	Light*				directionLight;		// ���C�g
	Enemy*				enemyShip;	// �G
	Bullet*				bullet;		// �e
	SkyBox*				skyBox;		// �X�J�C�{�b�N�X
	ShadowMapShader*	shadowMap;	// �V���h�[�}�b�v
	ScreenPolygon*		screenPolygon;// RHW�|���S��

	
public:
	Character*			ship;			// �v���[���[

	Scene00();
	~Scene00();

	void InitScene00();		// ������
	void Update();			// �X�V
	void Draw();			// �`��
	void Control();			// ����֐�
	void SetRenderState();	// �����_�����O��ݒ�

	bool CheckBB(Bullet* bullet, Enemy* enemy);		// �����蔻��(�����`)
	bool CheckBC(Bullet* bullet, Enemy* enemy);		// �����蔻��(�~)
};

#endif // !_SCENE00_H_

