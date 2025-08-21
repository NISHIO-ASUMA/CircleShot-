//=============================================
//
// �`���[�g���A��UI���� [ tutorialui.cpp ]
// Author: Asuma Nishio
//
//=============================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "tutorialui.h"
#include "manager.h"
#include "texture.h"

//==============================
// �R���X�g���N�^
//==============================
CTutorialUi::CTutorialUi()
{
	// �l�̃N���A
	m_nIdxTexture = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CTutorialUi::~CTutorialUi()
{
	// ����
}
//==============================
// ��������
//==============================
CTutorialUi* CTutorialUi::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	// �C���X�^���X����
	CTutorialUi* pTutoUi = new CTutorialUi;

	// �C���X�^���X�������s��
	if (pTutoUi == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTutoUi->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̊�{�ݒ�
	pTutoUi->SetPos(pos);
	pTutoUi->SetSize(fWidth, fHeight);
	pTutoUi->SetTexture(nType);

	// �������ꂽ�|�C���^��Ԃ�
	return pTutoUi;
}
//==============================
// ����������
//==============================
HRESULT CTutorialUi::Init(void)
{
	// �I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	// ���_�����^�C�v��ݒ�
	SetAnchor(CObject2D::ANCHORTYPE_CENTER);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==============================
// �I������
//==============================
void CTutorialUi::Uninit(void)
{
	// �I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}
//==============================
// �X�V����
//==============================
void CTutorialUi::Update(void)
{
	// �I�u�W�F�N�g2D�̍X�V����
	CObject2D::Update();
}
//==============================
// �`�揈��
//==============================
void CTutorialUi::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�擾
	CTexture * pTexture = CManager::GetTexture();

	// �擾��,null��������
	if (pTexture == nullptr) return;

	// ���蓖��
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}
//==============================
// �e�N�X�`�����蓖�ď���
//==============================
void CTutorialUi::SetTexture(int nType)
{
	// �e�N�X�`���|�C���^���擾
	CTexture* pTexture = CManager::GetTexture();

	// �擾��,null��������
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case 0:
		// �e�N�X�`�����蓖��
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\tutorial_menu.png");
		break;

	default:

		break;
	}
}
