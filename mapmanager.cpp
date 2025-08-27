//===========================================
//
// �}�b�v�}�l�[�W���[���� [ mapmanager.cpp ]
// Author : Asuma Nishio
//
//===========================================

//***************************
// �C���N���[�h�t�@�C��
//***************************
#include "mapmanager.h"
#include "mapobject.h"
#include "modellist.h"
#include "manager.h"

//=========================
// �R���X�g���N�^
//=========================
CMapManager::CMapManager(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_MapObj.clear();
	m_nSelectIdx = NULL;
}
//=========================
// �f�X�g���N�^
//=========================
CMapManager::~CMapManager()
{
	// ����
}
//=========================
// ������
//=========================
HRESULT CMapManager::Init(void)
{
	// ���������ʂ�Ԃ�
	return S_OK;
}
//=========================
// �I��
//=========================
void CMapManager::Uninit(void)
{
	// �l�̃N���A
	m_MapObj.clear();

	// ���g�̔j��
	CObject::Release();
}
//=========================
// �X�V
//=========================
void CMapManager::Update(void)
{

}
//=========================
// �`��
//=========================
void CMapManager::Draw(void)
{
	// m_MapObj[m_nSelectIdx]->Draw();

#if 0
	// ���X�g�擾
	CModelList::MODELINFO pModelList;

	// �z�u�������f���̃C���f�b�N�X���擾
	int nIdx = m_nIdxObj;

	// �͈̓`�F�b�N
	auto modelInfoVec = pModelList->GetInfo();

	if (nIdx < 0 || nIdx >= (int)modelInfoVec.size()) return;

	// ���f�������擾
	CModelList::MODELINFO& info = modelInfoVec[nIdx];

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

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)info.pBuffMat->GetBufferPointer();

	// �}�e���A����������
	for (int nCntMat = 0; nCntMat < (int)info.dwNumMat; nCntMat++)
	{
		D3DXMATERIAL Col = pMat[nCntMat];

		Col.MatD3D.Diffuse.a = 0.5f;

		// �}�e���A���ݒ�
		pDevice->SetMaterial(&Col.MatD3D);

		// ���f��(�p�[�c)�̕`��
		info.pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);
#endif
}
//=========================
// ��������
//=========================
CMapManager* CMapManager::Craete(void)
{
	// �C���X�^���X����
	CMapManager* pMapManager = new CMapManager;

	// null�Ȃ�
	if (pMapManager == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pMapManager->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pMapManager;
}













#if 0
// ���X�g�擾
CModelList* pModelList = CEditManager::GetList();

// �z�u�������f���̃C���f�b�N�X���擾
int nIdx = m_nSelectIndex;

// �͈̓`�F�b�N
auto modelInfoVec = pModelList->GetInfo();

// ���f�������擾
CModelList::MODELINFO& info = modelInfoVec[nIdx];

// �ړ�����
if (CManager::GetInputKeyboard()->GetPress(DIK_A))
{// A�L�[��������

	m_pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;
	m_pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}
}
else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
{// D�L�[��������
	// D�L�[�̂݉�����
	m_pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;
	m_pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}

}
else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
{// W�L�[��������

	m_pos.x += sinf(pCamera->GetRot().y) * 7.0f;
	m_pos.z += cosf(pCamera->GetRot().y) * 7.0f;

	// �p�x�𐳋K��
	if (m_rot.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_rot.y += D3DX_PI * 2.0f;
	}

}
else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
{// S�L�[��������

	m_pos.x -= sinf(pCamera->GetRot().y) * 7.0f;
	m_pos.z -= cosf(pCamera->GetRot().y) * 7.0f;

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}
	}
#endif
