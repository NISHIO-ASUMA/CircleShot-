//========================================
//
// �`���[�W���� [ charge.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "charge.h"
#include "manager.h"
#include "texture.h"

//**********************************
// ���O���
//**********************************
namespace CHARGEINFO
{
	constexpr float MAX_CHARGE = 100.0f;	// �ő�`���[�W��
};

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
float CCharge::m_fCharge = NULL;

//================================
// �R���X�g���N�^
//================================
CCharge::CCharge(int nPriority) : CGage(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
	m_nType = NULL;
}
//================================
// �f�X�g���N�^
//================================
CCharge::~CCharge()
{
	// ����
}
//================================
// ��������
//================================
CCharge* CCharge::Create(D3DXVECTOR3 pos,float fWidth, float fHeight, int nType)
{
	// �C���X�^���X����
	CCharge* pCharge = new CCharge;

	// null�Ȃ�
	if (pCharge == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pCharge->Init()))
	{
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pCharge->SetPos(pos);
	pCharge->SetSize(fWidth, fHeight);
	pCharge->SetType(nType);
	pCharge->SetTexture(nType);
	pCharge->SetAnchor(ANCHORTYPE_LEFTSIDE);

	// �������ꂽ�|�C���^��Ԃ�
	return pCharge;
}
//================================
// ���Z����
//================================
void CCharge::AddCharge(float fValue)
{
	m_fCharge += fValue;

	if (m_fCharge >= CHARGEINFO::MAX_CHARGE)
	{
		m_fCharge = CHARGEINFO::MAX_CHARGE;
	}
}
//================================
// ���Z����
//================================
void CCharge::DecCharge(float fValue)
{
	m_fCharge -= fValue;

	if (m_fCharge <= 0.0f)
	{
		m_fCharge = 0.0f;
	}
}
//================================
// ����������
//================================
HRESULT CCharge::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CCharge::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//================================
// �X�V����
//================================
void CCharge::Update(void)
{
	// ��ނ��o�[�̎�
	if (m_nType == CHARGE_BAR)
	{
		// �Q�[�W�̒����ݒ�
		FSetGageLength(CHARGEINFO::MAX_CHARGE, m_fCharge, 305.0f, 38.0f);
	}

	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//================================
// �`�揈��
//================================
void CCharge::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ǂݍ���
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// �e�N���X�̕`�揈��
	CObject2D::Draw();
}
//================================
// �e�N�X�`�����蓖�ď���
//================================
void CCharge::SetTexture(int nType)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ����null�Ȃ�
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case CHARGE_FRAME:	// �g
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\laser.png");
		break;

	case CHARGE_BAR:	// �{��
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\laser_gage.png");
		break;

	default:
		m_nIdxTex = -1;	// ��O�̒l
		break;
	}
}