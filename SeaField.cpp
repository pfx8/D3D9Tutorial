//*****************************************************************************
//
// �C�ʏ��� [SeaField.cpp]
//
// Author : LIAO HANCHEN
//
//*****************************************************************************
#include "SeaField.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
SeaField::SeaField()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
SeaField::~SeaField()
{

}

//*****************************************************************************
//
// ���W��ݒ�
//
//*****************************************************************************
HRESULT SeaField::InitPlane(D3DXVECTOR3 pos, D3DXVECTOR2 planeSize, D3DXVECTOR2 planeNum)
{
	m_pos = pos;	// �ʒu


	{
		m_vertexNum = (planeNum.x + 1) * (planeNum.y + 1);	// �����_��
		m_polygonNum = planeNum.x * planeNum.y * 2 + (planeNum.y - 1) * 4;		// �|���S����
		m_indexNum = (planeNum.x + 1) * 2 * planeNum.y + (planeNum.y - 1) * 2;	// �C���f�b�N�X��

		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		// ���_�V�F�[�_�[�錾
		{
			D3DVERTEXELEMENT9 planeDecl[] =		// ���_�f�[�^�̃��C�A�E�g���`
			{
				{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
				{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },
				{ 0, 24, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
				{ 0, 40, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
				D3DDECL_END()
			};
			pDevice->CreateVertexDeclaration(planeDecl, &m_vertexDecl);
		}

		// ���_�o�b�t�@�쐬
		{
			if (FAILED(pDevice->CreateVertexBuffer(m_vertexNum * sizeof(VERTEX_3D_2T), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D_2T, D3DPOOL_MANAGED, &m_vertexBuffer, NULL)))
			{
				std::cout << "[Error] ���_�o�b�t�@�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
				return E_FAIL;
			}

			VERTEX_3D_2T* VertexBuffer;

			// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@ �������ւ̃|�C���^���擾����
			m_vertexBuffer->Lock(0, 0, (void**)&VertexBuffer, 0);

			// ���_�o�b�t�@�̒��g�𖄂߂�
			// ���_���W(���[�J�����W = �`���`�����Ă�)
			// ���̎��g�̍��W�A���E�ł̍��W�ɂ͊֌W�Ȃ�
			// m_posFiled�͐��E�ł̈ʒu��

			for (int numY = 0; numY < (planeNum.y + 1); numY++)
			{
				for (int numX = 0; numX < (planeNum.x + 1); numX++)
				{
					// ���_���W�̐ݒ�
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.x = -(planeNum.x / 2.0f) * planeSize.x + numX * planeSize.x;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.y = 0.0f;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].position.z = (planeNum.y / 2.0f) * planeSize.y - numY * planeSize.y;
					// �@���x�N�g���̐ݒ�
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].normalVector = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
					// �e�N�X�`��1���W�̐ݒ�
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition1.x = numX * 1.0f;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition1.y = numY * 1.0f;
					// �e�N�X�`��2���W�̐ݒ�
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition2.x = numX * 0.8f;
					VertexBuffer[numY * (int(planeNum.x) + 1) + numX].texturePosition2.y = numY * 0.8f;
				}
			}

			// ���_�f�[�^���A�����b�N����
			m_vertexBuffer->Unlock();
		}

		// ���_�C���f�b�N�X�o�b�t�@�쐬
		{
			if (FAILED(pDevice->CreateIndexBuffer(m_indexNum * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_indexBuffer, NULL)))
			{
				std::cout << "[Error] ���_�C���f�N�X�������ł��Ȃ�!" << std::endl;	// �G���[���b�Z�[�W
				return E_FAIL;
			}

			WORD* vertexIndex = NULL;		// �C�f�b�N�X�̒��g�𖄂߂�

			m_indexBuffer->Lock(0, 0, (void**)&vertexIndex, 0);	// �C���f�b�N�X �f�[�^�̂�����͈͂����b�N���A���̃C���f�b�N�X �o�b�t�@�[ �������[�ւ̃|�C���^�[���擾����

			int index = 0;
			for (int numY = 0; numY < planeNum.y; numY++)
			{
				if (numY > 0)
				{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
					vertexIndex[index] = (numY + 1) * (planeNum.x + 1);
					index++;
				}

				for (int nCntVtxX = 0; nCntVtxX < (planeNum.x + 1); nCntVtxX++)
				{
					vertexIndex[index] = (numY + 1) * (planeNum.x + 1) + nCntVtxX;
					index++;
					vertexIndex[index] = numY * (planeNum.x + 1) + nCntVtxX;
					index++;
				}

				if (numY < (planeNum.y - 1))
				{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
					vertexIndex[index] = numY * (planeNum.x + 1) + planeNum.x;
					index++;
				}
			}

			m_indexBuffer->Unlock();	// �C���f�b�N�X �f�[�^�̃��b�N����������
		}
	}

	return S_OK;
}

//*****************************************************************************
//
// �`��
//
//*****************************************************************************
void SeaField::Draw(Shader* shader)
{
	PDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetVertexDeclaration(m_vertexDecl);								// ���_�錾��ݒ�
	pDevice->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX_3D_2T));		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C�i��
	pDevice->SetFVF(FVF_VERTEX_3D_2T);											// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetIndices(m_indexBuffer);										// ���_�C���f�b�N�X�o�b�t�@��ݒ�
	shader->m_effectPoint->SetTexture(shader->m_textureHandle, m_fieldTexture);	// �e�N�X�`���̐ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_vertexNum, 0, m_polygonNum);	// �|���S���̕`��
}