//====================================
//
// �G�f�B�^�[���� [ uiedit.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "uiedit.h"
#include "input.h"
#include "manager.h"
#include "ui.h"
#include <fstream>
#include <iomanip> 
#include <string>

//===============================
// �R���X�g���N�^
//===============================
CUiedit::CUiedit()
{
	// �z��N���A
	m_pUi.clear();
}
//===============================
// �f�X�g���N�^
//===============================
CUiedit::~CUiedit()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CUiedit::Init(void)
{
	// �z��N���A
	m_pUi.clear();

	return S_OK;
}
//===============================
// �I������
//===============================
void CUiedit::Uninit(void)
{
	// �z��N���A
	m_pUi.clear();
}
//===============================
// �X�V����
//===============================
void CUiedit::Update(void)
{
	// �L�[���͗p�̕ϐ�
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	// �ړ��ݒ�
	if (pInput->GetTrigger(DIK_A))
	{

	}
	else if (pInput->GetTrigger(DIK_D))
	{

	}
	else if (pInput->GetTrigger(DIK_W))
	{

	}
	else if (pInput->GetTrigger(DIK_S))
	{

	}

	// �z�u����L�[
	if (pInput->GetTrigger(DIK_RETURN))
	{// ui�ǉ�
		// AddUi()
	}

	// �폜�L�[
	if (pInput->GetTrigger(DIK_BACKSPACE))
	{

	}

	// �t�@�C�������o���L�[
	if (pInput->GetTrigger(DIK_F7))
	{
		SaveFile("data\\Ui.txt");
	}

	// �t�@�C���ēǂݍ��݃L�[
	if (pInput->GetTrigger(DIK_F8))
	{
		ReloadFile("data\\Ui.txt");
	}
}
//===============================
// �`�揈��
//===============================
void CUiedit::Draw(void)
{
	// �I�u�W�F�N�g�`��
	
}
//===============================
// ui�ǉ��֐�
//===============================
void CUiedit::AddUi(D3DXVECTOR3 pos, int type, float width, float height)
{
#if 0
	// Ui�𐶐�����
	CUi* pUi = CUi::Create(pos, type, width, height);

	// null�Ȃ�
	if (pUi == nullptr) return;

	// ���[�J���ϐ��錾
	EditInfo info;
	info.pos = pos; // ���W�Z�b�g
	info.nType = type; // ��ރZ�b�g
	info.fWidth = width; // �����Z�b�g
	info.fHeight = height; // �����Z�b�g

	info.pUi = pUi; // �|�C���^�Z�b�g

	// �z��ɒǉ�����
	m_pUi.push_back(info);
#endif
}
//===============================
// �����o������
//===============================
void CUiedit::SaveFile(const char* filename)
{
	// �����o���p�t�@�C���|�C���^�錾
	std::ofstream fStream(filename);

	// �J���Ȃ������珈���I��
	if (!fStream.is_open()) return;

	// �t�@�C���w�b�_�[
	fStream << "#===================================\n";
	fStream << "# UI�z�u���\n";
	fStream << "#===================================\n\n";

	// �z�u��
	fStream << "#===================================\n";
	fStream << "# �z�u��\n";
	fStream << "#===================================\n";
	fStream << "NUM_UI = " << m_pUi.size() << "\n\n";

	// �eUI���
	fStream << "#===================================\n";
	fStream << "# �eUI���\n";
	fStream << "#===================================\n\n";

	// 1�������o��
	for (int nUi = 0; nUi < m_pUi.size(); nUi++)
	{
		// �\���̏�����
		const EditInfo& ui = m_pUi[nUi];

		fStream << "#==========[" << nUi << "]�Ԗڂ̏��=========\n";
		fStream << "POS = "
			<< std::fixed << std::setprecision(2) // �v�f�������o���������߂�
			<< ui.pos.x << " "
			<< ui.pos.y << " "
			<< ui.pos.z << "\n";

		fStream << "TYPE = " << ui.nType << "\n";
		fStream << "WIDTH = " << ui.fWidth << "\n";
		fStream << "HEIGHT = " << ui.fHeight << "\n";
		fStream << "#================================\n\n";
	}

	// �t�@�C�������
	fStream.close();
}
//===============================
// �ēǂݍ��ݏ���
//===============================
void CUiedit::ReloadFile(const char* filename)
{
#if 0
	// �j��
	for (auto& UI : m_pUi) // �\���̂̌^��auto���g�p
	{
		// nullptr����Ȃ�������
		if (UI.pUi)
		{
			// �I������
			UI.pUi->Uninit();

			// �|�C���^�̔j��
			delete UI.pUi;
		}
	}

	// �z��̃N���A����
	m_pUi.clear();

	// �t�@�C���X�g���[���錾
	std::ifstream fStream(filename);

	// �J���Ȃ������珈���I��
	if (!fStream.is_open()) return;

	// line�ň�s���ǂ�ł���
	std::string line;

	// �z�u���擾�p
	int nNUmUi = 0;

	// �t�@�C���̍s��ǂ�ł���
	while (std::getline(fStream, line))
	{
		// "NUM_UI"��ǂݎ������
		if (line.find("NUM_UI") != std::string::npos)
		{
			// "="����������
			size_t pos = line.find('=');

			// "="�̎��̕������琔�l�����o��
			if (pos != std::string::npos)
			{
				// ���l�Z�b�g
				nNUmUi = std::stoi(line.substr(pos + 1));

				// while���𔲂���
				break;
			}
		}
	}

	// �eUI����ǂݍ���
	for (int nCnt = 0; nCnt < nNUmUi; nCnt++)
	{
		// ����p�ϐ��錾
		D3DXVECTOR3 pos = VECTOR3_NULL;
		int nType = 0;
		float fWidth = 0.0f;
		float fHeight = 0.0f;

		// ��s�����[�v�œǂ�ł���
		while (std::getline(fStream, line))
		{
			// "POS"��ǂݎ������
			if (line.find("POS") != std::string::npos)
			{
				// "="����������
				size_t posEqual = line.find('=');

				// "POS "���琔�l����
				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// POS���Z�b�g
					iss >> pos.x >> pos.y >> pos.z;
				}
			}
			else if (line.find("TYPE") != std::string::npos)
			{
				// "="����������
				size_t posEqual = line.find('=');

				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// ��ޑ��
					iss >> nType;
				}
			}
			else if (line.find("WIDTH") != std::string::npos)
			{
				// "="����������
				size_t posEqual = line.find('=');

				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// �������
					iss >> fWidth;
				}
			}
			else if (line.find("HEIGHT") != std::string::npos)
			{
				// "="����������
				size_t posEqual = line.find('=');

				if (posEqual != std::string::npos)
				{
					std::string valuePart = line.substr(posEqual + 1);
					std::istringstream iss(valuePart);

					// ��������
					iss >> fHeight;
				}
			}
			else if (line.find("#================================") != std::string::npos)
			{
				// 1UI���̓ǂݍ��݂�����������ǉ�
				AddUi(pos, nType, fWidth, fHeight);

				// while���𔲂���
				break;
			}
		}
	}

	// �t�@�C�������
	fStream.close();
#endif
}
