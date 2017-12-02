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
	TextureStruct m_FieldGrass = { "FieldGrass", "data/TEXTURE/field000.jpg", NULL };
	TextureStruct m_FieldStone = { "FieldStone", "data/TEXTURE/field001.jpg", NULL };
	TextureStruct m_FieldCheckered = { "FieldCheckered", "data/TEXTURE/field002.jpg", NULL};

	TextureStruct m_Null = { "NULL", NULL, NULL };

	std::map < std::string, TextureStruct> m_TextureList;	// �e�N�X�`�����X�g
	TextureStruct* GetTextureStruct(std::string name);	// �e�N�X�`�����擾
public:
	ResourcesManager();
	~ResourcesManager();

	LPDIRECT3DTEXTURE9	* LoadTexture(std::string name);	// �e�N�X�`����ǂݍ���
	void LoadMesh(std::string name);	// ���b�V����ǂݍ���

};

#endif // !_RESOURCES_MANAGER_H_

