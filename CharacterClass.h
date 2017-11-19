//*****************************************************************************
//
// �L�����N�^�[�x�[�X�N���X [CharacterClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_CLASS_H_
#define _CHARACTER_CLASS_H_

#include "Engine.h"

#include "MeshClass.h"
#include "MessageClass.h"
#include "BoundingBoxClass.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Character
{
private:
	// �Œ葮��
	D3DXVECTOR3		m_pos;		// �ʒu
	D3DXVECTOR3		m_rot;		// ��]
	D3DXVECTOR3		m_scl;		// �g��k��

	Mesh*			m_Mesh;			// ���b�V��
	OutputMessage*	m_Message;		// Debug���b�Z�[�W
	BoundingBox*	m_BoundingBox;	// �o�E���f�B���O�{�b�N�X

	std::string		m_name;		// �L�����N�^�[�̖��O�A����ɂ���ă��b�V���ƃe�N�X�`����T��

	float			m_Speed;		
public:
	Character();
	~Character();
	
	// �Վ��[�[���[���h�ϊ�
	void setWorldMatrix(D3DXMATRIX& mtxWorld);

	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void PosToMessageAndMessageDraw(int row);

	// ���W��ݒ�
	void InitCoordinate(D3DXVECTOR3 pos);

	// �L�����N�^�[�̖��O�����߂�
	void SetName(std::string name);

	// ���O�Ń��b�V�����쐬
	void ChooseMesh(std::string name);

	// �L�����N�^�[�̕`��
	void Draw();

	// �L�����N�^�[�ړ�
	void Move();

	// �L�����N�^�[�X�V
	void Update();

	// �L�����N�^�[�̃o�E���f�B���O�{�b�N�X���擾
	BoundingBox* GetBoundingBox();

	// �o�E���f�B���O�{�b�N�X�ʒu���擾
	D3DXVECTOR3* GetPosition();

	// �����蔻��
	bool CheckHitBB(Character* Object);
};


#endif // !_CHARACTER_CLASS_H_
