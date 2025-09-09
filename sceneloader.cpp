//====================================================
//
// �V�[���t�@�C���ǂݍ��ݏ��� [ sceneloader.cpp ]
// Author: Asuma Nishio
//
//====================================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "sceneloader.h"
#include "meshdome.h"
#include "meshfield.h"
#include "meshimpact.h"
#include "block.h"
#include "player.h"
#include "playerlifegage.h"
#include "bosslifegage.h"
#include "charge.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//=================================
// �R���X�g���N�^
//=================================
CSceneLoader::CSceneLoader()
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CSceneLoader::~CSceneLoader()
{
	// ����
}
//=================================
// ��������
//=================================
void CSceneLoader::SplitLoad(int nIdx)
{
	// �w��t�@�C�����J��
	std::ifstream loadFile(m_aFileList[nIdx]);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", m_aFileList[nIdx], MB_OK);

		return;
	}

	// ���[�J���ϐ�
	std::string line;
	int nNumFile = NULL;

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
				// �Q�[���v���C���[
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
				CBlock::Create(filePath.c_str(), pos, rot, size,type);

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