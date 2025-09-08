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
#include "tutotask.h"
#include "tutorialboss.h"

//==========================
// �R���X�g���N�^
//==========================
CTutorialManager::CTutorialManager()
{
	// �l�̃N���A
	m_pTutoui = nullptr;
	m_pTask = nullptr;
	m_Tasktype = TASKTYPE_MOVE;
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

	// ����
	CTutorialBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f));

	// �^�X�N����
	m_pTask = new CTutoTask;

	// null����Ȃ�������
	if (m_pTask != nullptr)
	{
		// ����������
		m_pTask->Init();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==========================
// �I������
//==========================
void CTutorialManager::Uninit(void)
{
	// null����Ȃ�������
	if (m_pTask != nullptr)
	{
		// �I������
		m_pTask->Uninit();

		// �j��
		delete m_pTask;

		// null������
		m_pTask = nullptr;
	}
}
//==========================
// �X�V����
//==========================
void CTutorialManager::Update(void)
{
	// �^�X�N�N���X�̍X�V����
	if (m_pTask != nullptr)
	{
		m_pTask->Update();
	}

	// ���̓f�o�C�X�擾
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// �擾���s��
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �ԍ��擾
	int nIdx = m_pTask->GetTaskIndex();

	// �Ǘ��t���O
	bool isCheck = false;
	bool isFinish = false;
	static bool isJump = false;

	// ���ݔԍ��ɉ����ĕύX
	switch (nIdx)
	{
	case CTutorialManager::TASKTYPE_MOVE:	// �ړ�����
		if ((pKey->GetPress(DIK_A) || pKey->GetPress(DIK_D)) ||
			(pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_RIGHT)))
		{
			isCheck = true;
		}

		break;

	case CTutorialManager::TASKTYPE_ATTACK:	// �U������

		if ((pKey->GetPress(DIK_RETURN) || pJoyPad->GetPress(pJoyPad->JOYKEY_X)))
		{
			isCheck = true;
		}

		break;
	case CTutorialManager::TASKTYPE_JUMP:	// �W�����v����

		if ((pKey->GetTrigger(DIK_SPACE) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A)))
		{
			isCheck = true;
		}

		break;

	case CTutorialManager::TASKTYPE_JUMPATTACK: // �W�����v�U��

		// �W�����v������t���O�𗧂Ă�
		if (pKey->GetTrigger(DIK_SPACE) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A))
		{
			isJump = true;
		}

		// �W�����v�ς݃t���O�������ԂōU��
		if (isJump && (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_X)))
		{
			isCheck = true;
			isJump = false; // ��x���������烊�Z�b�g
		}

		break;

	case CTutorialManager::TASKTYPE_LASER: // ����؂�ւ�

		if ((pKey->GetTrigger(DIK_F) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT_B)))
		{
			isCheck = true;
		}

		break;

	default:

		break;
	}

	// ���͂��L����,���ɐi��
	if (isCheck)
	{
		m_pTask->NextTask();
	}

	// ����L�[���� or �p�b�h��start�{�^�� ���� �I���t���O���L���Ȃ�
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && isFinish)
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetFade();

		// �Q�[���V�[���ɑJ��
		if (pFade != nullptr) pFade->SetFade(new CGame());
	}
}