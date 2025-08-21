//=================================================
//
// �`���[�g���A���Ǘ����� [ tutorialmanager.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "tutorialmanager.h"
#include "tutorialui.h"
#include "manager.h"
#include "fade.h"
#include "game.h"

//==========================
// �R���X�g���N�^
//==========================
CTutorialManager::CTutorialManager()
{
	// �l�̃N���A
	m_pTutoui = nullptr;
}
//==========================
// �f�X�g���N�^
//==========================
CTutorialManager::~CTutorialManager()
{
	// ����
}
//==========================
// ����������
//==========================
HRESULT CTutorialManager::Init(void)
{
	// ui����
	m_pTutoui = CTutorialUi::Create(D3DXVECTOR3(500.0f, 200.0f, 0.0f), 300.0f, 60.0f, 0);

	// �v���C���[����
	
	// ���������ʂ�Ԃ�
	return S_OK;
}
//==========================
// �I������
//==========================
void CTutorialManager::Uninit(void)
{
	// ����
}
//==========================
// �X�V����
//==========================
void CTutorialManager::Update(void)
{
	// ���̓f�o�C�X�擾
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// �擾���s��
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// ����L�[���� or �p�b�h��start�{�^��
	if (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START))
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetFade();

		// �Q�[���V�[���ɑJ��
		if (pFade != nullptr) pFade->SetFade(new CGame());
	}
}
