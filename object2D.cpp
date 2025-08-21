//====================================
//
// 2D�I�u�W�F�N�g���� [ object2D.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "enemy.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_Pos = VECTOR3_NULL;
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_Rot = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nAnchorType = ANCHORTYPE_NONE;
	m_nColorCount = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CObject2D::~CObject2D()
{
	// ����
}
//===============================
// ��������
//===============================
CObject2D* CObject2D::Create(void)
{
	// �|�C���^�錾
	CObject2D* pObject2D;

	// �C���X�^���X����
	pObject2D = new CObject2D;

	// ����������
	pObject2D->Init();

	return pObject2D;
}
//===============================
// �I�u�W�F�N�g2D����������
//===============================
HRESULT CObject2D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;	

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = 
	pVtx[1].pos = 
	pVtx[2].pos = 
	pVtx[3].pos = VECTOR3_NULL;

	// rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = COLOR_WHITE;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//===============================
// �I�u�W�F�N�g2D�I������
//===============================
void CObject2D::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}
//===============================
// �I�u�W�F�N�g2D�X�V����
//===============================
void CObject2D::Update(void)
{
	// �A���J�[�̎�ނ��擾
	switch (m_nAnchorType)
	{
	case ANCHORTYPE_NONE: // �����Ȃ�
		break;

	case ANCHORTYPE_CENTER: // ���S�_
		SetCenter();
		break;

	case ANCHORTYPE_LEFTSIDE: // ����_
		SetLeft();
		break;

	case ANCHORTYPE_RIGHTSIDE: // �E��_
		SetRight();
		break;

	default:
		SetCenter(); // ���S�_
		break;
	}
}
//===============================
// �I�u�W�F�N�g2D�`�揈��
//===============================
void CObject2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);
}
//======================================
// UV���W�ݒ�֐�
//======================================
void CObject2D::SetUV(float TexU,float TexV)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;	

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TexV);
	pVtx[3].tex = D3DXVECTOR2(TexU, TexV);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}
//==============================
// �I�u�W�F�N�g�_�Ŋ֐�
//==============================
void CObject2D::SetFlash(const int nFirstcount,const int nEndcount)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �C���N�������g���Ă���
	m_nColorCount++;

	// �J���[�ϐ�
	D3DXCOLOR col = COLOR_WHITE;

	if (m_nColorCount == nFirstcount)		// FirstCount�ƈ�v�����Ƃ�
	{
		//���_�J���[�̐ݒ�
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		// �J���[�Z�b�g
		SetCol(col);
	}
	else if (m_nColorCount == nEndcount)	// EndCount�ƈ�v�����Ƃ�
	{
		//���_�J���[�̐ݒ�
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �J���[�Z�b�g
		SetCol(col);

		// �����l�ɖ߂�
		m_nColorCount = NULL;
	}
		
	//�A�����b�N
	m_pVtxBuff->Unlock();
}
//======================================
// ���S����_�̃|���S��
//======================================
void CObject2D::SetCenter(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;	

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, 0.0f);

	// rhw�̐ݒ�( 1.0f�ŌŒ� )
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = D3DXCOLOR(m_col);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}
//======================================
// ������_�̃|���S��
//======================================
void CObject2D::SetLeft(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x,				m_Pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth,	m_Pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x,				m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth,	m_Pos.y + m_fHeight, 0.0f);

	// rhw�̐ݒ�( 1.0f�ŌŒ� )
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = D3DXCOLOR(m_col);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}
//======================================
// �E����_�̃|���S��
//======================================
void CObject2D::SetRight(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth,	m_Pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x ,				m_Pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth,	m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x,				m_Pos.y + m_fHeight, 0.0f);

	// rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw =
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = D3DXCOLOR(m_col);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}
