//==============================================
//
// ���U���g�V�[���Ǘ����� [ resultmanager.cpp ]
// Author: Asuma Nishio
// 
//==============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "resultmanager.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "resultui.h"

//=================================
// �R���X�g���N�^
//=================================
CResultManager::CResultManager()
{
	// �l�̃N���A
	m_isKeyDown = false;
}
//=================================
// �f�X�g���N�^
//=================================
CResultManager::~CResultManager()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CResultManager::Init(void)
{	
	// ui����
	CResultUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 360.0f, 0.0f), COLOR_WHITE, 350.0f, 200.0f, 0);

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_RESULTBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CResultManager::Uninit(void)
{
	// null�`�F�b�N

}
//=================================
// �X�V����
//=================================
void CResultManager::Update(void)
{
	// ���̓f�o�C�X���擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pJyoPad = CManager::GetJoyPad();

	// �擾���s��
	if (pInput == nullptr) return;
	if (pJyoPad == nullptr) return;

	// �J�������擾
	CCamera* pCamera = CManager::GetCamera();

	// �擾���s��
	if (pCamera == nullptr) return;

	// ����L�[�������ꂽ
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)) && !m_isKeyDown)
	{
		// �|�C���^�擾
		CFade* pFade = CManager::GetFade();

		// null����Ȃ��Ƃ�
		if (pFade != nullptr)
		{
			// �t���O�L����
			m_isKeyDown = true;

			// �V�[���J��
			pFade->SetFade(new CTitle(true));

			// �J�����̐ݒ������������
			pCamera->SetFinishRotation(false);
			pCamera->SetIsRotation(false);

			return;

		}
	}
}
