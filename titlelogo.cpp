//=========================================
//
// �^�C�g�����S���� [ titlelogo.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "titlelogo.h"
#include "manager.h"
#include "texture.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CTitleLogo::CTitleLogo(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTexIdx = NULL;
}
//================================
// �f�X�g���N�^
//================================
CTitleLogo::~CTitleLogo()
{
	// ����
}
//================================
// ��������
//================================
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nAnchorType)
{
	// �C���X�^���X����
	CTitleLogo* pTitlelogo = new CTitleLogo;

	// null�������ꍇ
	if (pTitlelogo == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTitlelogo->Init()))
	{
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pTitlelogo->SetPos(pos);
	pTitlelogo->SetSize(fWidth, fHeight);
	pTitlelogo->SetAnchor(nAnchorType);
	pTitlelogo->SetTexture();

	// �������ꂽ�|�C���^��Ԃ�
	return pTitlelogo;
}
//================================
// ����������
//================================
HRESULT CTitleLogo::Init(void)
{
	// �e�N���X�̏�����
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CTitleLogo::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//================================
// �X�V����
//================================
void CTitleLogo::Update(void)
{
	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//================================
// �`�揈��
//================================
void CTitleLogo::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// �e�N���X�̕`�揈��
	CObject2D::Draw();
}
//================================
// �e�N�X�`�����蓖�ď���
//================================
void CTitleLogo::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`�����蓖��
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\logo.png");
}
