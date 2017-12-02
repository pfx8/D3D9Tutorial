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
#include "Mesh.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ResourcesManager
{
private:
	// �e�N�X�`��
	std::map < std::string, std::string> m_TextureList;	// �e�N�X�`�����X�g
	std::string GetTextureStruct(std::string name);		// �e�N�X�`���p�X���擾

	// ���b�V��
	std::map < std::string, std::string> m_MeshList;	// ���b�V�����X�g
	std::string GetMeshPath(std::string name);		// ���b�V���p�X���擾
public:
	ResourcesManager();
	~ResourcesManager();

	HRESULT LoadTexture(std::string name, LPDIRECT3DTEXTURE9* texturePoint);	// �e�N�X�`����ǂݍ���
	HRESULT LoadMesh(std::string name, Mesh* mesh);	// ���b�V����ǂݍ���

};

#endif // !_RESOURCES_MANAGER_H_

