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
	LPD3DXBUFFER		m_D3DXBuffMatModel;	// �}�e���A�����ւ̃|�C���^
	DWORD			m_NumMatModel;		// �}�e���A�����̐�

public:
	Material();
	~Material();

	void SetMaterial();

	LPD3DXBUFFER* GetMaterialPoint();		// m_D3DXBuffMatModel�̎擾
	DWORD* GetMterialNumber();				// m_NumMatModel�̎擾
};

#endif // !_MATERIAL_H
