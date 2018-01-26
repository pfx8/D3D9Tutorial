//*****************************************************************************
//
// �L�����N�^�[�x�[�X���� [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include <map>

#include "Model.h"
#include "BoundingBox.h"
#include "..\Engine.h"
#include "..\DebugMessage.h"
#include "..\Shader\CelShader.h"

#define MAX_BACK_COEFFICIENT	(-0.18f)
#define MAX_FRONT_COEFFICIENT	(0.3f)

typedef enum
{
	LL_BACK = -1,	// [-1]���
	LL_STOP,		// [0]��~
	LL_FRONT,		// [1]�O�i
}LEVER_LEVEL;

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Character
{
private:
	UINT			m_leverLevel;		// �D�̃��o�[����
	double			m_speedCoefficient; // �X�s�[�h�Ɋւ���{��

public:
	DebugMessage*	m_message;		// Debug���b�Z�[�W
	float			m_waveAngle;	// �h��W��
	D3DXMATRIX		m_worldMatrix;	// ���[���h�ϊ��}�g���b�N�X

	// �x�N�g��
	D3DXVECTOR3		m_upVector;		// �J�����̏�����x�N�g��
	D3DXVECTOR3		m_lookVector;	// �J�����̒��������x�N�g��
	D3DXVECTOR3		m_rightVector;	// �J�����̉E�����x�N�g��

	// �Œ葮��
	D3DXVECTOR3		m_pos;			// �ʒu
	D3DXVECTOR3		m_rot;			// ��]
	D3DXVECTOR3		m_scl;			// �g��k��
	Model*			m_model;		// ���b�V��
	BoundingBox*	m_boundingBox;	// �o�E���f�B���O�{�b�N�X

	Character();
	~Character();

	void InitCharacter(D3DXVECTOR3 pos, D3DXVECTOR3 direction);		// ���W��ݒ�

	void PosToMessageAndMessageDraw(int row);	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void SetWorldMatrix();						// ���[���h�ϊ���ݒ�
	void Draw(CelShader* celShader);			// �L�����N�^�[�̕`��(Shader)
	
	void Update(float rot);				// �L�����N�^�[�X�V
	bool CheckHitBB(Character* Object);	// �����蔻��

	void RotationVecUp(float angle);			// ������̃x�N�g���ɂ��ĉ�]
	D3DXVECTOR3  MoveAlongVecLook(float unit);	// ���������ɉ����Ĉړ�

	void ChangeLever(LEVER_LEVEL scalars);		// ���o�[�̑���ɂ���ăX�s�[�h��ς��
};
#endif // !_CHARACTER_H_

