//*****************************************************************************
//
// �J�������� [Camera.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************

#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "Engine.h"

#include "DebugMessage.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Camera
{
private:
	D3DXVECTOR3		m_posEye;			// �J�����̈ʒu
	D3DXVECTOR3		m_posAt;			// �J�����̒����_
	D3DXVECTOR3		m_vecUP;			// �J�����̏�����x�N�g��

	D3DXVECTOR3		m_DirectionVector;	// �J���������x�N�g��


	//DebugMessage*	m_Message;
public:
	Camera();
	~Camera();

	// �J�������������֐�
	void InitCamera(D3DXVECTOR3 Eye, D3DXVECTOR3 At, D3DXVECTOR3 Up);

	// �r���[�C���O�ϊ�
	void setViewMatrix();

	// �v���W�F�N�V�����ϊ�(���e�ϊ�)
	void setProjMatrix();

	// �r���[�|�[�g��ݒ�
	void setViewport();

public: // ����
	
	// �����_
	void At(float move, char direction);

	// �J�����ʒu�𑀍삷��
	void Eye(float move, char direction);

	// ���W�����b�Z�[�W�ɓn���āA��ʂɕ`�悷��
	void PosToMessageAndMessageDraw(int row);

	// �J�����X�V
	void Update();
};


#endif // !_CAMERA_H_