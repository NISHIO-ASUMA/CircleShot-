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
#include "sceneloader.h"
#include <fstream>
#include <iostream>
#include <sstream>

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

	// �{�X����
	m_pBoss = CBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f), 60.0f, 1000);

	// �^�C�}�[����
	m_pTime = CTime::Create(D3DXVECTOR3(150.0f, 50.0f, 0.0f), 80.0f, 50.0f);

	// �V�[���I�u�W�F�N�g�ǂݍ���
	CSceneLoader::SplitLoad(1);

	// �t�@�C�����
	// CGameManager::Load();

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
//========================
// �ǂݍ��ݏ���
//========================
void CGameManager::Load(void)
{
	// �w��t�@�C�����J��
	std::ifstream loadFile("data\\SceneText\\GameObj.txt");

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", "data\\SceneText\\GameObj.txt", MB_OK);

		return;
	}

	// ���[�J���ϐ�
	std::string line;
	int nNumObj = NULL;

	// �ǂݍ��񂾖��O
	std::string objName, motionPath, filePath, createType;

	// �ǂݍ��ݏ��i�[
	D3DXVECTOR3 pos = VECTOR3_NULL;
	D3DXVECTOR3 rot = VECTOR3_NULL;
	int life = 0;
	float radius = 0.0f;
	float size = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
	int index = -1, type = -1, category = -1;

	// �ǂݍ��ݏI���܂ŉ�
	while (std::getline(loadFile, line))
	{
		// �R�����g��΂�
		if (line.empty() || line[0] == '#') continue;

		// �t�@�C���̓ǂݍ��ރ��C����I��
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "OBJNAME")
		{// "FILENAME"�ǂݎ�莞

			// ���������ĐV�����I�u�W�F�N�g�J�n
			objName.clear(); motionPath.clear(); filePath.clear(); createType.clear();

			pos = VECTOR3_NULL; 
			rot = VECTOR3_NULL;

			life = 0;

			radius = size = width = height = 0.0f;

			index = type = category = -1;

			std::string eq;

			iss >> eq >> objName;
		}
		else if (token == "POS")
		{
			std::string eq;
			iss >> eq >> pos.x >> pos.y >> pos.z;
		}
		else if (token == "ROT")
		{
			std::string eq;
			iss >> eq >> rot.x >> rot.y >> rot.z;
		}
		else if (token == "LIFE")
		{
			std::string eq;
			iss >> eq >> life;
		}
		else if (token == "INDEX")
		{
			std::string eq;
			iss >> eq >> index;
		}
		else if (token == "MOTIONPASS")
		{
			std::string eq;
			iss >> eq >> motionPath;
		}
		else if (token == "FILEPASS")
		{
			std::string eq;
			iss >> eq >> filePath;
		}
		else if (token == "TYPE")
		{
			std::string eq;
			iss >> eq >> type;
		}
		else if (token == "RADIUS")
		{
			std::string eq;
			iss >> eq >> radius;
		}
		else if (token == "SIZE")
		{
			std::string eq;
			iss >> eq >> size;
		}
		else if (token == "CREATETYPE")
		{
			std::string eq;
			iss >> eq >> createType;
		}
		else if (token == "WIDTH")
		{
			std::string eq;
			iss >> eq >> width;
		}
		else if (token == "HEIGHT")
		{
			std::string eq;
			iss >> eq >> height;
		}
		else if (token == "CATEGORY")
		{
			std::string eq;
			iss >> eq >> category;
		}
		else if (token == "ENDSET")
		{
			// �e�퐶��
			if (objName == "PLAYER")
			{
				// �v���C���[
				CPlayer::Create(pos, rot, life, index, motionPath.c_str());

				motionPath.clear();
			}
			else if (objName == "MESH")
			{
				// ���b�V��
				if (type == 0) CMeshDome::Create(pos, radius);

				else if (type == 1) CMeshField::Create(pos, radius);
			}
			else if (objName == "BLOCK")
			{
				// �u���b�N
				CBlock::Create(filePath.c_str(), pos, rot, size);

				filePath.clear();
			}
			else if (objName == "UI")
			{
				if (createType == "PLAYER")
				{
					CPlayerLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "BOSS")
				{
					CBossLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "LASER")
				{
					CCharge::Create(pos, width, height, category);
				}
			}
		}
	}

	// �t�@�C�������
	loadFile.close();
}

#if 0

//// �v���C���[����
//// �h�[������
//CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

//// �h�[������
//CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);

//// �t�B�[���h����
//CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

//CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 0, "data\\MOTION\\Player\\Player100motion.txt");
//CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 1, "data\\MOTION\\Player\\Player200motion.txt");

////�n�ʃu���b�N�z�u
//CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

//// �v���C���[�̗̓Q�[�W����
//CPlayerLifeGage::Create(D3DXVECTOR3(95.0f, 38.0f, 0.0f), 0.0f, 0.0f, CPlayerLifeGage::GAGE_BAR);
//CPlayerLifeGage::Create(D3DXVECTOR3(3.0f, 0.0f, 0.0f), 450.0f, 100.0f, CPlayerLifeGage::GAGE_FRAME);

//// �{�X�̗̓Q�[�W����
//CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), 0.0f, 0.0f, CBossLifeGage::TYPE_GAGE);
//CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), SCREEN_WIDTH * 0.4f, 60.0f, CBossLifeGage::TYPE_FRAME);

//// ���[�U�[�Q�[�W����
//CCharge::Create(D3DXVECTOR3(138.0f, 98.0f, 0.0f), 0.0f, 0.0f, CCharge::CHARGE_BAR);
//CCharge::Create(D3DXVECTOR3(0.0f, 95.0f, 0.0f), 450.0f, 45.0f, CCharge::CHARGE_FRAME);

#endif