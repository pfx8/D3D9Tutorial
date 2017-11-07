//*****************************************************************************
//
// �J�����N���X [CameraClass.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************

#ifndef _CAMERA_CLASS_H_
#define _CAMERA_CLASS_H_

#include "Main.h"

//*****************************************************************************
//
// �}�N����`
//
//*****************************************************************************


//*****************************************************************************
//
// �v���g�^�C�v�錾
//
//*****************************************************************************
class Camera
{
private:
	D3DXVECTOR3		m_posCameraEye;			// �J�����̎��_
	D3DXVECTOR3		m_posCameraAt;			// �J�����̒����_
	D3DXVECTOR3		m_vecCameraUP;			// �J�����̏�����x�N�g��

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

	// ���_
	void Eye(float move, char direction);
};


#endif // !_CAMERA_CLASS_H_