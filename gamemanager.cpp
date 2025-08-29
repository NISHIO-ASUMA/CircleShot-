//=========================================
//
// �Q�[���Ǘ����� [ gamemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "gamemanager.h"
#include "manager.h"
#include "debugproc.h"
#include "score.h"
#include "time.h"
#include "meshdome.h"
#include "meshfield.h"
#include "player.h"
#include "meshimpact.h"
#include "playerlifegage.h"
#include "bosslifegage.h"
#include "parameter.h"
#include "result.h"
#include "sound.h"
#include "item.h"
#include "barrierdurability.h"
#include "bullethorming.h"
#include "itemmanager.h"
#include "effectlaser.h"
#include "charge.h"

//**************************
// �ÓI�����o�ϐ��錾
//**************************
CMeshCylinder* CGameManager::m_pMeshCylinder = nullptr;	// �~��
CBoss* CGameManager::m_pBoss = nullptr;					// �{�X
CTime* CGameManager::m_pTime = nullptr;					// �^�C�}�[
CUimanager* CGameManager::m_puimanager = nullptr;		// UI�}�l�[�W���[
CBarrierManager* CGameManager::m_pBarrier = nullptr;	// �o���A�}�l�[�W���[
CRubbleManager* CGameManager::m_pRubble = nullptr;

//========================
// �R���X�g���N�^
//========================
CGameManager::CGameManager()
{
	// �l�̃N���A
}
//========================
// �f�X�g���N�^
//========================
CGameManager::~CGameManager()
{
	// ����
}
//========================
// ����������
//========================
HRESULT CGameManager::Init(void)
{
	// �V�����_�[����
	m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 550.0f);

	// �h�[������
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

	// �h�[������
	CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);

	// �t�B�[���h����
	CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

	// �{�X����
	m_pBoss = CBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f), 60.0f, 1000);

	// �v���C���[����
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 0, "data\\MOTION\\Player\\Player100motion.txt");
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 1, "data\\MOTION\\Player\\Player200motion.txt");

	//�n�ʃu���b�N�z�u
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

	// �v���C���[�̗̓Q�[�W����
	CPlayerLifeGage::Create(D3DXVECTOR3(95.0f, 38.0f, 0.0f), 0.0f, 0.0f, CPlayerLifeGage::GAGE_BAR);
	CPlayerLifeGage::Create(D3DXVECTOR3(3.0f, 0.0f, 0.0f), 450.0f, 100.0f, CPlayerLifeGage::GAGE_FRAME);

	// �{�X�̗̓Q�[�W����
	CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), 0.0f, 0.0f, CBossLifeGage::TYPE_GAGE);
	CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), SCREEN_WIDTH * 0.4f, 60.0f, CBossLifeGage::TYPE_FRAME);

	// ���[�U�[�Q�[�W����
	CCharge::Create(D3DXVECTOR3(138.0f, 98.0f, 0.0f), 0.0f, 0.0f, CCharge::CHARGE_BAR);
	CCharge::Create(D3DXVECTOR3(0.0f, 95.0f, 0.0f), 450.0f, 45.0f, CCharge::CHARGE_FRAME);

	// �^�C�}�[����
	m_pTime = CTime::Create(D3DXVECTOR3(150.0f, 50.0f, 0.0f), 80.0f, 50.0f);

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	 // �T�E���h�Đ�
	 pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);

	// �o���A�}�l�[�W���[����
	 m_pBarrier = new CBarrierManager;

	// null����Ȃ������珉����
	if (m_pBarrier != nullptr)
	{
		// ����������
		m_pBarrier->Init();
	}

	// ui�}�l�[�W���[����
	m_puimanager = new CUimanager;

	// null����Ȃ������珉����
	if (m_puimanager != nullptr)
	{
		// ����������
		m_puimanager->Init();
	}

	// ���I�I�u�W�F�N�g�}�l�[�W���[����
	m_pRubble = new CRubbleManager;

	// null����Ȃ������珉����
	if (m_pRubble != nullptr)
	{
		// ����������
		m_pRubble->Init();
	}

	// �A�C�e���}�l�[�W���[����
	m_pItemManager = new CItemManager;

	// null����Ȃ�������
	if (m_pItemManager != nullptr)
	{
		// ����������
		m_pItemManager->Init();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// �I������
//========================
void CGameManager::Uninit(void)
{
	// �g�p�����|�C���^��null������
	m_pBoss = nullptr;
	m_pMeshCylinder = nullptr;
	m_pTime = nullptr;

	// null����Ȃ�������
	if (m_puimanager != nullptr)
	{
		// �I������
		m_puimanager->Uninit();

		// �|�C���^�̔j��
		delete m_puimanager;

		// null������
		m_puimanager = nullptr;
	}

	// null����Ȃ�������
	if (m_pBarrier != nullptr)
	{
		// �I������
		m_pBarrier->Uninit();

		// �|�C���^�̔j��
		delete m_pBarrier;

		// null������
		m_pBarrier = nullptr;
	}

	// null����Ȃ�������
	if (m_pRubble != nullptr)
	{
		// �I������
		m_pRubble->Uninit();

		// �|�C���^�̔j��
		delete m_pRubble;

		// null������
		m_pRubble = nullptr;
	}

	// null����Ȃ�������
	if (m_pItemManager != nullptr)
	{
		// �I������
		m_pItemManager->Uninit();

		// �|�C���^�̔j��
		delete m_pItemManager;

		// null������
		m_pItemManager = nullptr;
	}
}
//========================
// �X�V����
//========================
void CGameManager::Update(void)
{
	// null����Ȃ�������
	if (m_pBarrier != nullptr)
	{
		// �X�V����
		m_pBarrier->Update();
	}

	// null����Ȃ�������
	if (m_pItemManager != nullptr)
	{
		// �X�V����
		m_pItemManager->Update();
	}
#ifdef _DEBUG

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_O))
	{
		CBulletHorming::Create("data\\MODEL\\ATTACKMODEL\\bulletobject000.x", D3DXVECTOR3(0.0f, 300.0f, 0.0f));
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_L))
	{
		// �t�@�C������
		m_pRubble->LoadSplitFile(m_pRubble->FILETYPE_SMALL);
	}

	if (CManager::GetInputKeyboard()->GetPress(DIK_Y))
	{
		// ���[�U�[�G�t�F�N�g����
		// CEffectLaser::Create(D3DXVECTOR3(0.0f, 50.0f, -550.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), LASER, 30.0f, 150, 50.0f);
		// CEffectLaser::Create(D3DXVECTOR3(0.0f, 10.0f, -550.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), COLOR_WHITE, 10.0f, 150, 30.0f);
		// CEffectLaser::Create(D3DXVECTOR3(0.0f, 50.0f, -550.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), LASER, 30.0f, 100, 30.0f);

	}

	// j�L�[
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_J))
	{
		// �J����
		CCamera* pCamera = CManager::GetCamera();

		// �v���C���[�擾
		CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
		if (pPlayer == nullptr) return;

		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		// ��������ƍ���
		float backDistance = 550.0f;
		float heightOffset = 150.0f;

		// �v���C���[�̌����̋t�������擾
		float rotY = pPlayer->GetRotDest().y;
		D3DXVECTOR3 backwardVec = D3DXVECTOR3(-sinf(rotY), 0.0f, -cosf(rotY));

		// �J�����ʒu
		D3DXVECTOR3 camPos = playerPos + backwardVec * backDistance;
		camPos.y += heightOffset; // �v���C���[��菭���キ�炢

		// ����
		D3DXVECTOR3 targetPos = playerPos + D3DXVECTOR3(0.0f, 250.0f, 0.0f); // Y��傫�����Č��グ��

		// �J�����`�F���W
		pCamera->SetCameraMode(pCamera->MODE_EVENT);

		// �C�x���g�J�����J�n
		pCamera->StartEventCamera(camPos, targetPos, 200);

		// �J�����̐U��
		pCamera->ShakeCamera(195);
	}

#endif // _DEBUG

}