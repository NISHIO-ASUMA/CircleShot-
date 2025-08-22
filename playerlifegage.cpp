//============================================
//
// �v���C���[�̗͏��� [ playerlifegage.cpp ]
// Author: Asuma Nishio
//
//============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "playerlifegage.h"
#include "player.h"
#include "parameter.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"

//========================
// �R���X�g���N�^
//========================
CPlayerLifeGage::CPlayerLifeGage(int nPriority) : CGage(nPriority)
{
	// �l�̃N���A
	m_pPlayer = nullptr;
	m_nLifeLength = NULL;
	m_gage = GAGE_FRAME;
	m_nMaxLifeLength = NULL;
}
//========================
// �f�X�g���N�^
//========================
CPlayerLifeGage::~CPlayerLifeGage()
{
	// ����
}
//========================
// ����������
//========================
HRESULT CPlayerLifeGage::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// null��������
	if (m_pPlayer == nullptr)
	{
		// �v���C���[�擾
		m_pPlayer = CPlayer::GetIdxPlayer(1);
	}

	// �擾�ł�����
	if (m_pPlayer != nullptr)
	{
		// �p�����[�^�[�擾
		CParameter* pParam = m_pPlayer->GetParameter();

		// ���݂̗̑͂��擾����
		m_nMaxLifeLength = pParam->GetHp();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// �I������
//========================
void CPlayerLifeGage::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//========================
// �X�V����
//========================
void CPlayerLifeGage::Update(void)
{
	// null����Ȃ� ���� ��ނ��o�[�̎�
	if (m_pPlayer != nullptr && m_gage == GAGE_BAR)
	{
		// �p�����[�^�[�擾
		CParameter* pParam = m_pPlayer->GetParameter();

		// ���݂̗̑͂��擾����
		m_nLifeLength = pParam->GetHp();

		// �Q�[�W�̒����ݒ�
		SetGageLength(m_nMaxLifeLength, m_nLifeLength, 0.28f, GAGE_HEIGHT);
	}

	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//========================
// �`�揈��
//========================
void CPlayerLifeGage::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ǂݍ���
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �e�N���X�̕`��
	CObject2D::Draw();
}
//========================
// ��������
//========================
CPlayerLifeGage* CPlayerLifeGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype)
{
	// �C���X�^���X����
	CPlayerLifeGage* pLifeGage = new CPlayerLifeGage;

	// null��������
	if (pLifeGage == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pLifeGage->Init()))
	{
		// null��Ԃ�
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pLifeGage->SetPos(pos);
	pLifeGage->SetSize(fWidth, fHeight);
	pLifeGage->SetGage(gagetype);
	pLifeGage->SetTexture(gagetype);
	pLifeGage->SetAnchor(CObject2D::ANCHORTYPE_LEFTSIDE);

	// �������ꂽ�|�C���^��Ԃ�
	return pLifeGage;
}
//========================
// �e�N�X�`�����蓖�ď���
//========================
void CPlayerLifeGage::SetTexture(int Type)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ��ނɉ����Ċ��蓖��
	switch (Type)
	{
	case GAGE_FRAME:	// �t���[��
		// ���蓖��
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\playerlife_frame000.png");
		break;

	case GAGE_BAR:	// �{�̃Q�[�W
		// ���蓖��
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\playerlife_gage000.png");
		break;

	default:
		m_nIdxTexture = -1;
		break;
	}
}
