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
#include "meshdome.h"
#include "meshfield.h"
#include "block.h"
#include "camera.h"
#include "rubblemanager.h"
#include "rubble.h"

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
	// �h�[������
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

	// �t�B�[���h����
	CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

	// �u���b�N�z�u
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

	// �����o�ϐ�������
	m_nSelectIndex = -1;
	m_moveSpeed = 1.5f;
	m_rotSpeed = 0.03f;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=============================
// �I������
//=============================
void CEditManager::Uninit(void)
{
	// null�`�F�b�N

}
//=============================
// �X�V����
//=============================
void CEditManager::Update(void)
{
	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();



}
//=============================
// �f�[�^�Z�[�u����
//=============================
void CEditManager::Save(void)
{

}
