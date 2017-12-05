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

public:
	LPD3DXMESH			m_meshPoint;			// ���b�V�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9*	m_meshTexturePoint;	// �e�N�X�`���}�l�W�����g
	Material*				m_material;			// �}�e���A�����ւ̃|�C���^

	Mesh();
	~Mesh();

	void DrawModel();	// ���f����`�悷��
	void DrawModel(IDirect3DVertexShader9* vertexShader, IDirect3DVertexDeclaration9* vertexDecl);	// ���f����`�悷��(Shader)
};

#endif // !_MESH_H_

