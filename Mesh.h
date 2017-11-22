//*****************************************************************************
//
// ���b�V������ [Mesh.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _MESH_H_
#define _MESH_H_

#include "Engine.h"

#include "Material.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class Mesh
{
private:
	LPD3DXMESH		m_mesh;		// ���b�V�����ւ̃|�C���^
	Material*			m_material;	// �}�e���A�����ւ̃|�C���^
	std::string		m_path;		// ���f���̃p�X

	PDIRECT3DTEXTURE9	m_MeshTexturePoint;		// �e�N�X�`���}�l�W�����g

public:
	Mesh();
	~Mesh();

	// �g���������b�V����ǂݍ���
	void SetMesh(std::string path);

	// X�t�@�C����ǂݍ���
	HRESULT ReadXFile();

	// ���f����`�悷��
	void DrawModel();

	// ���b�V���Ƀe�N�X�`����ݒ肷��
	void SetMeshTexture(PDIRECT3DTEXTURE9* texturePoint);
};

#endif // !_MESH_H_

