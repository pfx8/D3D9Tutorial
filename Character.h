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
	DebugMessage*	m_message;		// Debug���b�Z�[�W
	std::string		m_name;			// �L�����N�^�[�̖��O�A����ɂ���ă��b�V���ƃe�N�X�`����T��

public:
	// �Œ葮��
	D3DXVECTOR3		m_pos;		// �ʒu
	D3DXVECTOR3		m_speed;		// �X�s�[�h
	D3DXVECTOR3		m_rot;		// ��]
	D3DXVECTOR3		m_scl;		// �g��k��
	Mesh*			m_mesh;		// ���b�V��
	BoundingBox*		m_boundingBox;	// �o�E���f�B���O�{�b�N�X

	Character();
	~Character();

	void InitCharacter(D3DXVECTOR3 pos);	// ���W��ݒ�
	void SetWorldMatrix(D3DXMATRIX* mtxWorld);		// �Վ��[�[���[���h�ϊ�

	void SetName(std::string name) { m_name = name; };
	std::string GetName() { return m_name; };

	void PosToMessageAndMessageDraw(int row);	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void Draw();	// �L�����N�^�[�̕`��
	void Draw(ID3DXEffect* effect);	// �L�����N�^�[�̕`��(Effect)
	void Draw(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl);	// �L�����N�^�[�̕`��(Shader)
	void Move();	//  �Վ��[�[�L�����N�^�[�ړ�
	
	void Update(D3DXVECTOR3* pos, D3DXVECTOR3* speed, D3DXMATRIX* worldMatrix);	// �L�����N�^�[�X�V
	bool CheckHitBB(Character* Object);	// �����蔻��

};
#endif // !_CHARACTER_H_

