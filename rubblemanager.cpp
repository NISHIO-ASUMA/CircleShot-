//=================================================
//
// ���I�I�u�W�F�N�g�Ǘ����� [ rubblemanager.cpp ]
// Author : Asuma Nishio
//
//=================================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "rubblemanager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
std::vector<CRubble*>CRubbleManager::m_rubbles = {}; // ���I�z��
int CRubbleManager::m_nIdxCount = NULL;	// �C���f�b�N�X�J�E���g

//=====================================
// �R���X�g���N�^
//=====================================
CRubbleManager::CRubbleManager()
{
	// �l�̃N���A
	m_rubbles.clear();
}
//=====================================
// �f�X�g���N�^
//=====================================
CRubbleManager::~CRubbleManager()
{
	// ����
}
//=====================================
// ����������
//=====================================
HRESULT CRubbleManager::Init(void)
{
	// �l�̃N���A
	m_rubbles.clear();

	// �t�@�C���ǂݍ���
	Load();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CRubbleManager::Uninit(void)
{
	// �l�̃N���A
	m_rubbles.clear();
}
//=====================================
// �X�V����
//=====================================
void CRubbleManager::Update(void)
{
	// ����
}
//=====================================
// �t�@�C���ǂݍ��݊֐�
//=====================================
void CRubbleManager::Load(void)
{
	// �ǂݍ��ރt�@�C���p�X��ݒ�
	std::ifstream loadFile(FILEPASS);
	
	// �t�@�C����O�`�F�b�N
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", FILEPASS, MB_OK);
		return;
	}
	
	// �ǂݍ��ލs��ݒ�
	std::string loadline;
	
	int nNumAll = NULL; // ����
	
	// NUM_RUBBLES �ǂݎ��
	while (std::getline(loadFile, loadline))
	{
		std::istringstream iss(loadline);
		std::string token;
		iss >> token;

		if (token == "NUM_RUBBLES")
		{
			std::string eq;
			iss >> eq >> nNumAll;
			break;
		}
	}

	// �I�u�W�F�N�g�������ɓǂݍ���
	for (int nCnt = 0; nCnt < nNumAll; nCnt++)
	{
		D3DXVECTOR3 pos = VECTOR3_NULL;
		D3DXVECTOR3 rot = VECTOR3_NULL;
		std::string filePath;

		bool inSetting = false;

		while (std::getline(loadFile, loadline))
		{
			// ��s,�R�����g�X�L�b�v
			if (loadline.empty() || loadline[0] == '#') continue;

			std::istringstream iss(loadline);
			std::string token;
			iss >> token;

			if (token == "SETTING")
			{
				// �����\��ԂɕύX
				inSetting = true;
			}
			else if (token == "POS")
			{
				std::string eq;

				iss >> eq >> pos.x >> pos.y >> pos.z; // ���W���
			}
			else if (token == "ROT")
			{
				std::string eq;

				iss >> eq >> rot.x >> rot.y >> rot.z; // �p�x���
			}
			else if (token == "FILEPASS")
			{
				std::string eq;

				iss >> eq >> filePath; // ���f���t�@�C���p�X
			}
			else if (token == "END_SETTING" && inSetting)
			{
				// �I�u�W�F�N�g����
				CRubbleManager::Create(pos, rot, filePath.c_str());

				// ���̃I�u�W�F�N�g��
				break; 
			}
		}
	}

	// �t�@�C�������
	loadFile.close();
}
//=====================================
// ��������
//=====================================
CRubble* CRubbleManager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// �C���X�^���X����
	CRubble* pNewBlock = CRubble::Create(pos,rot,pFilename);

	// �C���X�^���X�̐������ł�����
	if (pNewBlock)
	{
		// �z��ɒǉ�
		m_rubbles.push_back(pNewBlock);

		// �C���f�b�N�X
		m_nIdxCount++;

		// �������ꂽ�|�C���^��Ԃ�
		return pNewBlock;
	}
	else
	{
		// ���ɂ��Ȃ��|�C���^��Ԃ�
		return nullptr;
	}
}
