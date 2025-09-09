//==========================================
//
// �^�C�g���Ǘ����� [ titlemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "titlemanager.h"
#include "titleui.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "input.h"
#include "block.h"
#include "meshfield.h"
#include "meshdome.h"
#include "titleplayer.h"
#include "ui.h"
#include "sound.h"
#include "titlelogo.h"
#include "edit.h"
#include "pausemanager.h"
#include "pointui.h"

//============================
// �R���X�g���N�^
//============================
CTitleManager::CTitleManager(bool isCreate) : m_isFirstuiCreate(isCreate)
{
	// �l�̃N���A
	m_nIdx = NULL;

	for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
	{
		m_pTitleui[nCnt] = nullptr;
	}
	m_pPointUi = nullptr;
	m_isuiCreate = false;
}
//============================
// �f�X�g���N�^
//============================
CTitleManager::~CTitleManager()
{
	// ����
}
//============================
// ����������
//============================
HRESULT CTitleManager::Init(void)
{	
	// ���̃V�[��������߂��Ă����Ƃ�
	if (!m_isFirstuiCreate) 
	{
		// ����W��ݒ�
		D3DXVECTOR3 CenterPos = D3DXVECTOR3(210.0f, 540.0f, 0.0f);

		// �^�C�g����ui�𐶐�
		for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
		{
			// ���̊Ԋu���󂯂�
			D3DXVECTOR3 pos = CenterPos;

			pos.x += nCnt * INTERVAL;

			// ui�𐶐�
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, UIWIDTH, UIHEIGHT, nCnt);
		}

		// �t���O��L����
		m_isuiCreate = true;
	}

	// �n�ʐ���
	CMeshField::Create(VECTOR3_NULL, FIELDWIDTH);

	// ���󃁃b�V���𐶐�
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 500.0f);

	// �^�C�g���v���C���[�𐶐�
	CTitlePlayer::Create(D3DXVECTOR3(180.0f,0.0f,0.0f),VECTOR3_NULL, 0, "data\\MOTION\\Player\\TitlePlayer100.txt");
	CTitlePlayer::Create(D3DXVECTOR3(260.0f,0.0f,0.0f),VECTOR3_NULL, 1, "data\\MOTION\\Player\\TitlePlayer200.txt");

	// �^�C�g�����S����
	CTitleLogo::Create(D3DXVECTOR3(200.0f, 90.0f, 0.0f), 200.0f, 60.0f, 1);

	// UI����
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f),30, 200.0f, 60.0f, "data\\TEXTURE\\Enterkey.png", true);

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	// pSound->PlaySound(CSound::SOUND_LABEL_TITLE_BGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CTitleManager::Uninit(void)
{
	// ����
}
//============================
// �X�V����
//============================
void CTitleManager::Update(void)
{
	// ���̓f�o�C�X�擾
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// �擾���s��
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return;

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �擾���s��
	if (pCamera == nullptr) return;

	// �L�[���͎� ���� ui����������Ă��Ȃ�������
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && !m_isuiCreate)
	{
		// ����W��ݒ�
		D3DXVECTOR3 CenterPos = D3DXVECTOR3(210.0f, 540.0f, 0.0f);

		// �^�C�g����ui�𐶐�
		for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
		{
			// ���̊Ԋu���󂯂�
			D3DXVECTOR3 pos = CenterPos;

			pos.x += nCnt * INTERVAL;

			// ui�𐶐�
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, UIWIDTH, UIHEIGHT, nCnt);
		}

		// null�Ȃ�
		if (!m_pPointUi)
		{
			// �ŏ��͑I�𒆂�UI�ʒu
			D3DXVECTOR3 pos = m_pTitleui[m_nIdx]->GetPos(); 

			// �I�����j���[�̏�ɐ���
			pos.y -= 100.0f; 

			// ���UI����
			m_pPointUi = CPointUi::Create(pos);
		}

		// �t���O��L����
		m_isuiCreate = true;
	}

	// ��L�[����
	if (pKey->GetTrigger(DIK_LEFT) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT) || pKey->GetTrigger(DIK_A))
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// �C���f�b�N�X�ԍ������Z
		m_nIdx--;

		// �ŏ��l�ȉ��Ȃ�ŏ��l�ɐݒ�
		if (m_nIdx < SELECT_START)
			m_nIdx = SELECT_END;
	}

	// ���L�[����
	if (pKey->GetTrigger(DIK_RIGHT) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_RIGHT) || pKey->GetTrigger(DIK_D))
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// �C���f�b�N�X�ԍ������Z
		m_nIdx++;

		// �ő�l�ȏ�Ȃ�ő�l�ɐݒ�
		if (m_nIdx > SELECT_END)
			m_nIdx = SELECT_START;
	}

	// �t�F�[�h�擾
	CFade* pFade = CManager::GetFade();

	// null��������
	if (pFade == nullptr) return;

	// �I������Ă��郁�j���[�̃|���S���J���[��ύX
	for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
	{
		// null����Ȃ�������
		if (m_pTitleui[nCnt] != nullptr)
		{
			// �J���[�ύX
			if (nCnt == m_nIdx)
			{// �I������Ă������
				// �J���[�Z�b�g
				m_pTitleui[nCnt]->SetCol(COLOR_WHITE);
			}
			else
			{// �I�����ꂽ���Ȃ�����
				// �J���[�Z�b�g
				m_pTitleui[nCnt]->SetCol(COLOR_GLAY);
			}
		}
	}

	// null����Ȃ�������
	if (m_pPointUi && m_pTitleui[m_nIdx])
	{
		// ���W��h��
		D3DXVECTOR3 pos = m_pTitleui[m_nIdx]->GetPos();

		// ��ɃZ�b�g
		pos.y -= 100.0f; 

		// ���W�����킹��
		m_pPointUi->SetPos(pos);
	}

	// Enter�L�[ or Start�{�^��
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && pCamera->GetFinishRotation())
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_RETURN);

		switch (m_nIdx)
		{
		case CTitleUi::MENU_GAME:		// �Q�[�����[�h
			if (pFade != nullptr) pFade->SetFade(new CGame());	// �Q�[���V�[���ɑJ��
			break;

		case CTitleUi::MENU_TUTORIAL:	// �`���[�g���A�����[�h
			if (pFade != nullptr) pFade->SetFade(new CTutorial());	// �`���[�g���A���V�[���ɑJ��
			break;

		case CTitleUi::MENU_EXIT:	// �I�����j���[
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}

#ifdef _DEBUG

	// F2�L�[
	if ((pKey->GetTrigger(DIK_F9)))
	{
		// �ҏW���
		if (pFade != nullptr) pFade->SetFade(new CEdit());
	}

#endif // _DEBUG

}