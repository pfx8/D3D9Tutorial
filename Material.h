//*****************************************************************************
//
// �}�e���A������ [Material.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Engine.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Material
{
private:


public:
	D3DMATERIAL9*		m_materialPoint;	// �}�e���A�����ւ̃|�C���^
	DWORD			m_materialNum;	// �}�e���A�����̐�

	Material();
	~Material();

	void SetMaterial();
};

#endif // !_MATERIAL_H
