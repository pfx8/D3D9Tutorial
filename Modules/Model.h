//*****************************************************************************
//
// ���f������ [Model.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MODEL_H_
#define _MODEL_H_

#include "../Engine.h"

#include "Material.h"
#include "../Shader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Model
{
private:

public:
	LPD3DXMESH			m_meshPoint;		// ���b�V�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9*	m_meshTexturePoint;	// �e�N�X�`���}�l�W�����g
	Material*			m_material;			// �}�e���A�����ւ̃|�C���^

	Model();
	~Model();

	void DrawModel(Shader* shader);	// ���f����`�悷��
};

#endif // !_MODEL_H_

