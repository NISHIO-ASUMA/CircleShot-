//============================================
//
// �V�[���h�ϋv�l�֐� [ barrierdurability.h ]
// Author : Asuma Nishio
// 
// TODO : �������͕`����Ǘ����邾��!
//
//============================================

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "barrierdurability.h"
#include "manager.h"
#include "texture.h"

//=======================================
// �I�[�o�[���[�h�R���X�g���N�^
//=======================================
CBarrierDurability::CBarrierDurability(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_isCreate = false;
	m_nIdxTex = NULL;
	m_nDurability = NULL;
}
//=======================================
// �f�X�g���N�^
//=======================================
CBarrierDurability::~CBarrierDurability()
{
	// ����
}
//=======================================
// ��������
//=======================================
CBarrierDurability* CBarrierDurability::Create(D3DXVECTOR3 pos, float fHeight, float fWidth, int nType)
{
	// �C���X�^���X������
	CBarrierDurability* pbarrier = new CBarrierDurability;

	// null�Ȃ�
	if (pbarrier == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pbarrier->SetPos(pos);
	pbarrier->SetSize(fWidth, fHeight);
	pbarrier->SetTexture(nType);
	pbarrier->SetAnchor(ANCHORTYPE_CENTER);

	// ���������s��
	if (FAILED(pbarrier->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pbarrier;
}
//=======================================
// ����������
//=======================================
HRESULT CBarrierDurability::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// �I�u�W�F�N�g�̎�ޒ�`
	SetObjType(TYPE_BARRIER);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=======================================
// �I������
//=======================================
void CBarrierDurability::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//=======================================
// �X�V����
//=======================================
void CBarrierDurability::Update(void)
{
	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//=======================================
// �`�揈��
//=======================================
void CBarrierDurability::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// null�Ȃ�
	if (pDevice == nullptr) return;

	// �}�l�[�W���[����|�C���^�擾
	CTexture* pTex = CManager::GetTexture();

	// null�Ȃ�
	if (pTex == nullptr) return;

	// �e�N�X�`�����Z�b�g����
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdxTex));

	// �e�N���X�̕`��
	CObject2D::Draw();
}
//=======================================
// �e�N�X�`�����蓖�ď���
//=======================================
void CBarrierDurability::SetTexture(int nType)
{
	// �}�l�[�W���[����|�C���^�擾
	CTexture* pTex = CManager::GetTexture();

	// null�Ȃ�
	if (pTex == nullptr) return;
}
//=======================================
// �ϋv�l���Z����
//=======================================
void CBarrierDurability::AddBarrier(int nValue)
{
	// ����l�ȏ�Ȃ�
	if (m_nDurability >= 3) return;

	// ���Z����
	m_nDurability += nValue;
}

