//*****************************************************************************
//
// �G���f�B���O���� [SceneEnding.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCENE_ENDING_H_
#define _SCENE_ENDING_H_

#include "Modules\Scene.h"
#include "Shader\RHWShader.h"
#include "Engine.h"
#include "ResourcesManager.h"

//*****************************************************************************
//
// �N���X�錾
//
//*****************************************************************************
class SceneEnding : public Scene
{
private:
	RHWShader*					m_RHWshader;

public:
	ResourcesManager*			m_resourcesManager;	// ���\�[�X�}�l�W�����g
	IDirect3DVertexDeclaration9*m_vertexDecl;	// ���_�V�F�[�_�[�錾
	LPDIRECT3DVERTEXBUFFER9		m_vertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9		m_indexBuffer;	// ���_�C���f�b�N�X�o�b�t�@
	LPDIRECT3DTEXTURE9			m_texture;	// �t�B�[���h�e�N�X�`��
	
	SceneEnding();
	~SceneEnding();

	HRESULT MakeVertexDecl();	// ���_�쐬
	void Draw();
};

#endif // !_SCENE_SceneEnding_H_

