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
#include "mapobject.h"
#include "template.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//=============================
// �R���X�g���N�^
//=============================
CEditManager::CEditManager()
{
	// �l�̃N���A
	m_nSelectIndex = NULL;
	m_moveSpeed = NULL;
	m_rotSpeed = NULL;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nIdx = NULL;
	m_mtxworld = {};

	m_nSavePassIdx = NULL;
	m_nNumAll = NULL;

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
	m_moveSpeed = 5.0f;

	// �ǂݍ���
	CModelList::Load();

	// ����
	m_pMapManager = CMapManager::Craete();
	
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
	// �J����
	CCamera* pCamera = CManager::GetCamera();

	// �ړ�����
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// A�L�[��������

		m_pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
		m_pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// D�L�[��������
		// D�L�[�̂݉�����
		m_pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
		m_pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * m_moveSpeed;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// W�L�[��������

		m_pos.x += sinf(pCamera->GetRot().y) * m_moveSpeed;
		m_pos.z += cosf(pCamera->GetRot().y) * m_moveSpeed;

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// S�L�[��������

		m_pos.x -= sinf(pCamera->GetRot().y) * m_moveSpeed;
		m_pos.z -= cosf(pCamera->GetRot().y) * m_moveSpeed;
	}

	// �����ύX
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_R))
	{
		m_pos.y += 20.0f;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_F))
	{
		m_pos.y -= 20.0f;
	}

	// �p�x�ύX ( Y )
	if (CManager::GetInputKeyboard()->GetPress(DIK_Y))
	{
		m_rot.y += 0.03f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_H))
	{
		m_rot.y -= 0.03f;
	}

	// �p�x�ύX ( X )
	if (CManager::GetInputKeyboard()->GetPress(DIK_U))
	{
		m_rot.x += 0.03f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_J))
	{
		m_rot.x -= 0.03f;
	}

	// �p�x�ύX ( Z )
	if (CManager::GetInputKeyboard()->GetPress(DIK_I))
	{
		m_rot.z += 0.03f;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_K))
	{
		m_rot.z -= 0.03f;
	}

	// ����������
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_TAB))
	{
		m_rot = VECTOR3_NULL;
	}

	// �C���f�b�N�X�����Z ���Z
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_E) && m_nIdx < 3)
	{
		m_nIdx++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_Q)&& m_nIdx >= 0)
	{
		m_nIdx--;

		//if (m_nIdx <= 0)
		//{
		//	m_nIdx = 0;
		//}
	}

	// ���K���֐�
	m_rot.x = NormalAngle(m_rot.x);
	m_rot.y = NormalAngle(m_rot.y);
	m_rot.z = NormalAngle(m_rot.z);

	// �L�[���͂ŕۑ�
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F7))
	{
		// �����ɕۑ��֐��ǉ�
		Save();
	}

	// �ۑ��p�X�؂�ւ�����
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F6))
	{
		m_nSavePassIdx = (m_nSavePassIdx + 1) % SAVEPASS_MAX;
	}

	// �L�[���͂Ő���
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ��������
		CMapObject* pMapObj = CMapObject::Create(m_pos, m_rot, m_nIdx);

		// �z��ɒǉ�
		m_pMapManager->PushBack(pMapObj);

		// ���������Z
		m_nNumAll++;
	}
}
//=============================
// �`�揈��
//=============================
void CEditManager::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);
	
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���݂̃}�g���b�N�X�̎擾
	pDevice->GetMaterial(&matDef);

	// ���f�����
	CModelList::MODELINFO Info = CModelList::GetInfo(m_nIdx);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)Info.pBuffMat->GetBufferPointer();

	// �}�e���A����������
	for (int nCntMat = 0; nCntMat < (int)Info.dwNumMat; nCntMat++)
	{
		// �J���[
		D3DXMATERIAL Col = pMat[nCntMat];

		Col.MatD3D.Diffuse.a = 0.5f;

		// �}�e���A���ݒ�
		pDevice->SetMaterial(&Col.MatD3D);

		// �C���f�b�N�X�ɉ����ĕύX����
		if (Info.pTexture[nCntMat] != -1)
		{
			// �e�N�X�`���擾
			CTexture* pTexture = CManager::GetTexture();

			// �e�N�X�`���Z�b�g
			pDevice->SetTexture(0, pTexture->GetAddress(Info.pTexture[nCntMat]));
		}
		else
		{
			pDevice->SetTexture(0, NULL); // �e�N�X�`���Ȃ�
		}

		// ���f��(�p�[�c)�̕`��
		Info.pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//=============================
// �`�揈��
//=============================
void CEditManager::Save(void)
{
	// �t�@�C���ɕۑ�
	// FILELIST[m_nSavePassIdx]
}
