//=========================================
//
// ���f���t�@�C�����X�g [ modellist.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "modellist.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "manager.h"

//****************************
// �ÓI�����o�ϐ��錾
//****************************
std::vector<CModelList::MODELINFO> CModelList::m_ModelInfo = {}; // ���I���X�g

//======================
// �R���X�g���N�^
//======================
CModelList::CModelList()
{
	// 
}
//======================
// �f�X�g���N�^
//======================
CModelList::~CModelList()
{
	// ����
}
//=========================
// ���f�����ǂݍ��ݏ���
//=========================
void CModelList::Load(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �w��t�@�C�����J��
	std::ifstream loadFile(MODELLIST);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", MODELLIST, MB_OK);

		return;
	}

	// ���[�J���ϐ�
	std::string line;
	int nNumFile = NULL;

	// �z��̃N���A����
	m_ModelInfo.clear();

	// �ǂݍ��ݏI���܂ŉ�
	while (std::getline(loadFile, line))
	{
		// �t�@�C���̓ǂݍ��ރ��C����I��
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_MODELFILE")
		{// "NUM_FILE"�ǂݎ�莞

			// "="�̎�
			std::string eq;

			// ���
			iss >> eq >> nNumFile;

			// �t�@�C���z��̃T�C�Y���m��
			m_ModelInfo.reserve(nNumFile);
		}
		else if (token == "FILENAME")
		{// "FILENAME"�ǂݎ�莞

			// �\���̕ϐ�
			MODELINFO info = {};

			// �N���A
			ZeroMemory(&info, sizeof(MODELINFO));

			// �t�@�C����
			std::string eq, filepath;

			iss >> eq >> filepath;

			// ������擾
			strncpy_s(info.FileName, filepath.c_str(), sizeof(info.FileName) - 1);

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(info.FileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&info.pBuffMat,
				NULL,
				&info.dwNumMat,
				&info.pMesh);

			// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL* pMat = nullptr;

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)info.pBuffMat->GetBufferPointer();

			// �e�N�X�`���C���f�b�N�X�z��
			info.pTexture.resize(info.dwNumMat, -1);

			// �}�e���A����������
			for (int nCntMat = 0; nCntMat < (int)info.dwNumMat; nCntMat++)
			{
				// �e�N�X�`�����ǂݍ��߂���
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �e�N�X�`���|�C���^�擾
					CTexture* pTexture = CManager::GetTexture();

					// �e�N�X�`���Z�b�g
					int texID = pTexture->Register(pMat[nCntMat].pTextureFilename);

					// �e�N�X�`�������i�[
					info.pTexture[nCntMat] = texID;
				}
				else
				{
					// �e�N�X�`���Ȃ�
					info.pTexture[nCntMat] = -1;
				}
			}

			// �z��ǉ�
			m_ModelInfo.push_back(info);
		}
	}

	// �t�@�C�������
	loadFile.close();
}
//======================
// �j��
//======================
void CModelList::UnLoad(void)
{
	// �z��N���A
	m_ModelInfo.clear();
}
