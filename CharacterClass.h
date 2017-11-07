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

class Character
{
private:
	// �Œ葮��
	D3DXVECTOR3		m_pos;
	D3DXVECTOR3		m_rot;
	D3DXVECTOR3		m_scl;

	Mesh*			m_Mesh;

public:
	Character();
	~Character();
	
	// �Վ��[�[���[���h�ϊ�
	void setWorldMatrix();

	// �L�����N�^�[�̃��b�V���̎擾
	Mesh* GetMesh();
};


#endif // !_CHARACTER_CLASS_H_
