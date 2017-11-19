//*****************************************************************************
//
// ���b�V���N���X [MeshClass.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_CLASS_H_
#define _MESH_CLASS_H_

#include "Engine.h"

#include "MaterialClass.h"
#include "TextureManagerClass.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Mesh
{
private:
	LPD3DXMESH		m_mesh;				// ���b�V�����ւ̃|�C���^
	Material*		m_material;			// �}�e���A�����ւ̃|�C���^

	TextureManager* m_textureManager;	// �e�N�X�`���}�l�W�����g

	std::string		m_path;				// ���f���̃p�X
public:
	Mesh();
	~Mesh();

	// �g���������b�V����ǂݍ���
	void SetMesh(std::string path);

	// X�t�@�C����ǂݍ���
	HRESULT ReadXFile();

	// ���f����`�悷��
	void DrawModel();
};

#endif // !_MESH_CLASS_H_

