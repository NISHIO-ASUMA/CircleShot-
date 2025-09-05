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
#include "sceneloader.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "meshfield.h"
#include "player.h"

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
	// �V�����_�[����
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 550.0f);

	// �h�[������
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

	// �h�[������
	CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);

	// �t�B�[���h����
	CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

	// �v���C���[����
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 0, "data\\MOTION\\Player\\TutoPlayer100motion.txt");
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 1, "data\\MOTION\\Player\\TutoPlayer200motion.txt");

	//�n�ʃu���b�N�z�u
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

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
	if (pKey->GetTrigger(DIK_P) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START))
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetFade();

		// �Q�[���V�[���ɑJ��
		if (pFade != nullptr) pFade->SetFade(new CGame());
	}
}
