//*****************************************************************************
//
// ���W�ϊ��ςݒ��_��2D�|���S����`�� [ScreenPolygon.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCREEN_POLYGON_H_
#define _SCREEN_POLYGON_H_

#include "..\Engine.h"
#include "..\ResourcesManager.h"
#include "..\Shader\RHWShader.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class ScreenPolygon
{
private:
	RHWShader*					m_RHWshader;		// �ϊ��ςݗp�V�F�[�_�[

	void DrawObject(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DTEXTURE9 texture);	// �e���̂�`�悷��
	void MakeVertexDecl();	// ���_�錾
	HRESULT MakeVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint);	// ���_�쐬
	HRESULT MakeIndex();	// �C���f�b�N�X�쐬
public:
	ResourcesManager*			m_resourcesManager;	// ���\�[�X�}�l�W�����g
	IDirect3DVertexDeclaration9*m_vertexDecl;		// ���_�V�F�[�_�[�錾
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;		// ���_�C���f�b�N�X�o�b�t�@

	LPDIRECT3DVERTEXBUFFER9		m_UIminiMapVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_UIminiMapTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9		m_UIHPVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_UIHPTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9		m_UIKeyVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9			m_UIKeyTexture;			// �t�B�[���h�e�N�X�`��

	ScreenPolygon();
	~ScreenPolygon();

	void Draw();
};


#endif // !_SCREEN_POLYGON_H_