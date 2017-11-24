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

#include <map>

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
	D3DXVECTOR3		m_Speed;		// �X�s�[�h
	D3DXVECTOR3		m_rot;		// ��]
	D3DXVECTOR3		m_scl;		// �g��k��

	Mesh*			m_Mesh;			// ���b�V��
	DebugMessage*		m_Message;		// Debug���b�Z�[�W
	BoundingBox*		m_BoundingBox;	// �o�E���f�B���O�{�b�N�X

	std::string		m_name;			// �L�����N�^�[�̖��O�A����ɂ���ă��b�V���ƃe�N�X�`����T��
	
	std::map<std::string, void*> m_MemberList;// �v���C�x�[�g�����o�[���X�g
	void InitMemberList();// �v���C�x�[�g�����o�[���X�g������
public:
	Character();
	~Character();

	bool		m_BoundingBoxON;	// �o�E���f�B���O�{�b�N�X��`�悷��

	// ���W��ݒ�
	void InitCharacter(D3DXVECTOR3 pos, PDIRECT3DTEXTURE9* texturePoint, std::string meshPath);
	// �Վ��[�[���[���h�ϊ�
	void SetWorldMatrix(D3DXMATRIX& mtxWorld);

	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void PosToMessageAndMessageDraw(int row);

	// �L�����N�^�[�̕`��
	void Draw();

	//  �Վ��[�[�L�����N�^�[�ړ�
	void Move();

	// �L�����N�^�[�X�V
	void Update();
	// ���b�V�����擾
	Mesh* GetMesh();

	// �����蔻��
	bool CheckHitBB(Character* Object);

	// �擾
	// �L�����N�^�[�̃o�E���f�B���O�{�b�N�X���擾
	BoundingBox* GetBoundingBox();
	// �L�����N�^�[�ʒu���擾
	D3DXVECTOR3* GetPosition();


	//*****************************************************************************
	//
	// �v���C�x�[�g�����o�[���擾
	//
	//*****************************************************************************
	/*template <typename T> T* GetMember(std::string MemberName)
	{
		if (m_MemberList.find(MemberName) != m_MemberList.end())
		{
			return dynamic_cast<T*> m_MemberList[MemberName];
		}
	};*/

	/*auto* GetMember(std::string MemberName)
	{
		if (m_MemberList->find(MemberName) != m_MemberList->end())
		{
			return m_MemberList->at(MemberName);
		}
	};*/

	auto* GetMember(std::string MemberName)
	{
		if (m_MemberList.find(MemberName) != m_MemberList.end())
		{
			return m_MemberList[MemberName];
		}
	};
};

#endif // !_CHARACTER_H_

