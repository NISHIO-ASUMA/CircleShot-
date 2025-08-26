//========================================
//
// �G�f�B�^�[�V�[������ [ edit.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "edit.h"
#include "editmanager.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CEdit::CEdit() : CScene(CScene::MODE_EDIT)
{
	// �l�̃N���A
	m_pEditManager = nullptr;
}
//================================
// �f�X�g���N�^
//================================
CEdit::~CEdit()
{
	// ����
}
//================================
// ��������
//================================
CEdit* CEdit::Create(void)
{
	// �C���X�^���X����
	CEdit* pEdit = new CEdit;

	// null�Ȃ�
	if (pEdit == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pEdit->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pEdit;
}
//================================
// ����������
//================================
HRESULT CEdit::Init(void)
{
	// �}�l�[�W���[�̃C���X�^���X����
	m_pEditManager = new CEditManager;

	// null����Ȃ�������
	if (m_pEditManager != nullptr)
	{
		// ����������
		m_pEditManager->Init();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CEdit::Uninit(void)
{
	// null����Ȃ�������
	if (m_pEditManager != nullptr)
	{
		// �}�l�[�W���[�̏I������
		m_pEditManager->Uninit();

		// �|�C���^�̔j��
		delete m_pEditManager;

		// null������
		m_pEditManager = nullptr;
	}
}
//================================
// �X�V����
//================================
void CEdit::Update(void)
{
	// null����Ȃ�������
	if (m_pEditManager != nullptr)
	{
		// �}�l�[�W���[�̍X�V����
		m_pEditManager->Update();
	}
}
//================================
// �`�揈��
//================================
void CEdit::Draw(void)
{
	// ����
}
