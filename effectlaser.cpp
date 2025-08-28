//============================================
//
// ���[�U�[�G�t�F�N�g���� [ effectlaser.cpp ]
// Author: Asuma Nishio
//
//============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "effectlaser.h"
#include "manager.h"
#include "texture.h"

//====================================
// �I�[�o�[���[�h�R���X�g���N�^
//====================================
CEffectLaser::CEffectLaser(int nPriority) : CBillboard(nPriority)
{
	m_nIdxTex = NULL;
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
}
//====================================
// �f�X�g���N�^
//====================================
CEffectLaser::~CEffectLaser()
{
	// ����
}
//====================================
// ��������
//====================================
CEffectLaser* CEffectLaser::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// �C���X�^���X����
	CEffectLaser* pLaser = new CEffectLaser;

	// null�Ȃ�
	if (pLaser == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pLaser->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�Z�b�g
	pLaser->SetTexture();
	pLaser->SetPos(pos);
	pLaser->SetSize(fRadius, fRadius);
	pLaser->SetCol(col);

	// TODO : �����o�|�C���^�ɑ��
	
	// �������ꂽ�|�C���^��Ԃ�
	return pLaser;
}
//====================================
// ����������
//====================================
HRESULT CEffectLaser::Init(void)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//====================================
// �I������
//====================================
void CEffectLaser::Uninit(void)
{
	// �e�N���X�̏I��
	CBillboard::Uninit();
}
//====================================
// �X�V����
//====================================
void CEffectLaser::Update(void)
{
	// �e�N���X�̍X�V����
	CBillboard::Update();
}
//====================================
// �`�揈��
//====================================
void CEffectLaser::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// ���u�����f�B���O�̉��Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g��K�p
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �r���{�[�h�`��
	CBillboard::Draw();

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���u�����f�B���O��߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
//====================================
// �e�N�X�`�����蓖�ď���
//====================================
void CEffectLaser::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�Ȃ�
	if (pTexture == nullptr) return;

	// �e�N�X�`�����蓖��
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\effect000.jpg");
}