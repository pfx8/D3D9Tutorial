//*****************************************************************************
//
// ���W�ϊ��ςݒ��_��2D�|���S����`�� [ScreenPolygon.h]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#ifndef _SCREEN_POLYGON_H_
#define _SCREEN_POLYGON_H_

#include "Character.h"
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
	RHWShader*	RHWshader;	// �ϊ��ςݗp�V�F�[�_�[

	void DrawObject(LPDIRECT3DVERTEXBUFFER9 vertexBuffer, LPDIRECT3DTEXTURE9 texture);					// �e���̂�`�悷��
	void MakeVertexDecl();																				// ���_�錾
	HRESULT MakeVertex(D3DXVECTOR2 pos, D3DXVECTOR2 size, LPDIRECT3DVERTEXBUFFER9* vertexBufferPoint);	// ���_�쐬
	HRESULT MakeIndex();																				// �C���f�b�N�X�쐬

public:
	ResourcesManager*				resourcesManager;		// ���\�[�X�}�l�W�����g

	IDirect3DVertexDeclaration9*	vertexDecl;				// ���_�V�F�[�_�[�錾
	LPDIRECT3DINDEXBUFFER9			indexBuffer;			// ���_�C���f�b�N�X�o�b�t�@

	LPDIRECT3DVERTEXBUFFER9			UIminiMapVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIminiMapTexture;		// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIminiMapPlayerVertexBuffer;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIminiMapPlayerTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIminiMapEnemyVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIminiMapEnemyTexture;			// �t�B�[���h�e�N�X�`��

	LPDIRECT3DVERTEXBUFFER9			UIHPVertexBuffer[3];	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIHPTexture;			// �t�B�[���h�e�N�X�`��
	int								HP;

	LPDIRECT3DVERTEXBUFFER9			UIKeyVertexBuffer;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9				UIKeyTexture;			// �t�B�[���h�e�N�X�`��

	ScreenPolygon();
	~ScreenPolygon();

	void Draw();
	void Update(Character* player, Character* enemy);
};


#endif // !_SCREEN_POLYGON_H_