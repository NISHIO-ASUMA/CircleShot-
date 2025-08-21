//=====================================
//
// �U���O�����o [ attacksign.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "attacksign.h"
#include "manager.h"
#include "texture.h"

//**********************
// ���O���
//**********************
namespace ATTACKSIGN
{
	inline constexpr int LIFE = 60; // �ő����
	const D3DXVECTOR3 SIGNPOS = { 640.0f,60.0f,0.0f }; // UI���W
};

//==============================
// �R���X�g���N�^
//==============================
CAttackSign::CAttackSign(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nidxTex = NULL;
	m_nLife = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CAttackSign::~CAttackSign()
{
	// ����
}
//==============================
// ����������
//==============================
HRESULT CAttackSign::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// ������ݒ�
	m_nLife = ATTACKSIGN::LIFE;
	
	// ���������ʂ�Ԃ�
	return S_OK;
}
//==============================
// �I������
//==============================
void CAttackSign::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//==============================
// �X�V����
//==============================
void CAttackSign::Update(void)
{
	// �_�ŏ��������s
	SetFlash(2, 5);

	// �̗͂����炷
	m_nLife--;

	// 0�ȉ�
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();

		// �����ŏ����I��
		return;
	}

	// �I�u�W�F�N�g�X�V
	CObject2D::Update();
}
//==============================
// �`�揈��
//==============================
void CAttackSign::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nidxTex));

	// �I�u�W�F�N�g�`��
	CObject2D::Draw();
}
//==============================
// �e�N�X�`�����蓖��
//==============================
void CAttackSign::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �p�X��ݒ�
	m_nidxTex = pTexture->Register("data\\TEXTURE\\alert.png");
}
//==============================
// ��������
//==============================
CAttackSign* CAttackSign::Create(float fWidth, float fHeight)
{
	// �C���X�^���X����
	CAttackSign* pAttack = new CAttackSign;

	// null�`�F�b�N
	if (pAttack == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pAttack->SetPos(ATTACKSIGN::SIGNPOS);
	pAttack->SetSize(fWidth, fHeight);
	pAttack->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pAttack->SetTexture();

	// ���������s��
	if (FAILED(pAttack->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pAttack;
}