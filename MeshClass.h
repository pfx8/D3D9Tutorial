//*****************************************************************************
//
// ���b�V���N���X [MeshClass.h]
//
// Author : �����E�@�J���V��
//
//*****************************************************************************
#ifndef _MESH_CLASS_H_
#define _MESH_CLASS_H_

#include "Main.h"

#include "MaterialClass.h"
#include "TextureManagerClass.h"

class Mesh
{
private:
	LPD3DXMESH		m_mesh;		// ���b�V�����ւ̃|�C���^
	Material*		m_material; // �}�e���A�����ւ̃|�C���^

	TextureManager* m_textureManager; // �e�N�X�`���}�l�W�����g


	// �Վ�
	//LPD3DXBUFFER		m_D3DXBuffMatModel = NULL;	// �}�e���A�����ւ̃|�C���^
	//DWORD				m_NumMatModel = NULL;		// �}�e���A�����̐�
	//LPDIRECT3DTEXTURE9	m_TexturePoint = NULL;
public:
	Mesh();
	~Mesh();

	// X�t�@�C����ǂݍ���
	HRESULT ReadXFile();

	// ���f����`�悷��
	void DrawModel();
};

#endif // !_MESH_CLASS_H_

