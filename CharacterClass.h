//*****************************************************************************
//
// �L�����N�^�[�x�[�X�N���X [CharacterClass.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _CHARACTER_CLASS_H_
#define _CHARACTER_CLASS_H_

#include "Main.h"

#include "MeshClass.h"
#include "TextureManagerClass.h"
#include "MessageClass.h"

class Character
{
private:
	// �Œ葮��
	D3DXVECTOR3		m_pos;		// �ʒu
	D3DXVECTOR3		m_rot;		// ��]
	D3DXVECTOR3		m_scl;		// �g��k��

	Mesh*			m_Mesh;		// ���b�V��

	OutputMessage*	m_Message;	// Debug���b�Z�[�W

	std::string		m_name;		// �L�����N�^�[�̖��O�A����ɂ���ă��b�V���ƃe�N�X�`����T��
public:
	Character();
	~Character();
	
	// �Վ��[�[���[���h�ϊ�
	void setWorldMatrix(D3DXMATRIX& mtxWorld);

	// �L�����N�^�[�̃��b�V���̎擾
	Mesh* GetMesh();

	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void PosToMessageAndMessageDraw(int row);

	// ���W��ݒ�
	void InitCoordinate(D3DXVECTOR3 pos);

	// �L�����N�^�[�̖��O�����߂�
	void SetName(std::string name);

	// ���O�Ń��b�V�����쐬
	void ChooseMesh(std::string name);
};


#endif // !_CHARACTER_CLASS_H_
