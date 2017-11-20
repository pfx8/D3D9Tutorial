//*****************************************************************************
//
// ���\�[�X�Ǘ��N���X [ResourcesManager.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "Engine.h"

#include <map>

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ResourcesManager
{
private:
	Texture m_FieldGrass = { "FieldGrass", "data/TEXTURE/field000.jpg", NULL };
	Texture m_FieldStone = { "FieldStone", "data/TEXTURE/field001.jpg", NULL };
	Texture m_FieldCheckered = { "FieldCheckered", "data/TEXTURE/field002.jpg", NULL};
	Texture m_Null = { "Null", NULL, NULL };

	// �e�N�X�`�����X�g
	std::map < std::string, LPDIRECT3DTEXTURE9> m_TextureList;

	// �e�N�X�`����ǂݍ���
	HRESULT LoadTexture(Texture* texture);

public:
	ResourcesManager();
	~ResourcesManager();

	// �e�N�X�`�����X�g������������
	void InitTextureList();

	// �e�N�X�`�����擾
	LPDIRECT3DTEXTURE9* GetTexture(std::string name);
};

#endif // !_RESOURCES_MANAGER_H_

