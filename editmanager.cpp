//================================================
//
// �G�f�B�^�[�V�[���Ǘ����� [ editmanager.cpp ]
// Author : Asuma Nishio
//
//================================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "editmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "rubblemanager.h"
#include "rubble.h"
#include "editmodel.h"
#include "mapmanager.h"

//=============================
// �R���X�g���N�^
//=============================
CEditManager::CEditManager()
{
	// �l�̃N���A
	m_nSelectIndex = NULL;
	m_moveSpeed = NULL;
	m_rotSpeed = NULL;

	for (int nCnt = 0; nCnt < MAX_EDITOBJ; nCnt++)
	{
		m_pRubbleObj[nCnt] = nullptr;
	}

	m_pMapManager = nullptr;
}
//=============================
// �f�X�g���N�^
//=============================
CEditManager::~CEditManager()
{
	// ����
}
//=============================
// ����������
//=============================
HRESULT CEditManager::Init(void)
{
	// �����o�ϐ�������
	m_nSelectIndex = 0;
	m_moveSpeed = 1.5f;
	m_rotSpeed = 0.03f;

	// �ǂݍ���
	CModelList::Load();

	m_pMapManager = CMapManager::Craete(VECTOR3_NULL,NULL);
	
	// ���������ʂ�Ԃ�
	return S_OK;
}
//=============================
// �I������
//=============================
void CEditManager::Uninit(void)
{
	// �j��
	CModelList::UnLoad();
}
//=============================
// �X�V����
//=============================
void CEditManager::Update(void)
{

}
//=============================
// �`�揈��
//=============================
void CEditManager::Draw(void)
{
	// �}�l�[�W���[�`��
	m_pMapManager->Draw();
}
