//*****************************************************************************
//
// �L�����N�^�[�x�[�X���� [Character.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Engine.h"

#include "Mesh.h"
#include "DebugMessage.h"
#include "BoundingBox.h"

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
	DebugMessage*		m_Message;		// Debug���b�Z�[�W
	BoundingBox*		m_BoundingBox;	// �o�E���f�B���O�{�b�N�X

	std::string		m_name;			// �L�����N�^�[�̖��O�A����ɂ���ă��b�V���ƃe�N�X�`����T��

	float			m_Speed;		
public:
	Character();
	~Character();

	// ���W��ݒ�
	void SetCoordinate(D3DXVECTOR3 pos);
	// �Վ��[�[���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);
	// �L�����N�^�[�̖��O�����߂�
	void SetName(std::string name);

	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void PosToMessageAndMessageDraw(int row);

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
	// ���b�V�����擾
	Mesh* GetMesh();

	// �����蔻��
	bool CheckHitBB(Character* Object);


};


#endif // !_CHARACTER_H_
