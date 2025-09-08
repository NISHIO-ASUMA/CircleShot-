//==========================================
//
// �`���[�g���A���{�X���� [ tutoboss.cpp ]
// Author: Asuma Nishio
//
//==========================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "tutoboss.h"
#include "manager.h"

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CTutoBoss::CTutoBoss(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pMotion = nullptr;
	m_mtxworld = {};

	for (int nCnt = 0; nCnt < TUTOMODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_nType = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CTutoBoss::~CTutoBoss()
{
	// ����
}
//==============================
// ��������
//==============================
CTutoBoss* CTutoBoss::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �C���X�^���X����
	CTutoBoss* pTutoBoss = new CTutoBoss();
	if (pTutoBoss == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pTutoBoss->m_pos = pos;
	pTutoBoss->m_rot = rot;

	// ���������s��
	if (FAILED(pTutoBoss->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pTutoBoss;
}
//==============================
// ����������
//==============================
HRESULT CTutoBoss::Init(void)
{

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_BOSS);

	// �^�C�v���
	m_nType = CTutoBoss::TYPE_MAX;

	// ���[�V�����̓ǂݍ���
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\TutoBoss.txt", TUTOMODEL, m_pModel, CTutoBoss::TYPE_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(m_nType);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==============================
// �I������
//==============================
void CTutoBoss::Uninit(void)
{
	// ���f�������̔j��
	for (int nCnt = 0; nCnt < TUTOMODEL; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_pModel[nCnt] != nullptr)
		{
			// �I������
			m_pModel[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_pModel[nCnt];

			// nullptr�ɂ���
			m_pModel[nCnt] = nullptr;
		}
	}

	// nullptr�`�F�b�N
	if (m_pMotion != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pMotion;

		// nullptr�ɂ���
		m_pMotion = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//==============================
// �X�V����
//==============================
void CTutoBoss::Update(void)
{
	// null�`�F�b�N
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(m_pModel,TUTOMODEL);
	}
}
//==============================
// �`�揈��
//==============================
void CTutoBoss::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

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

	// �S���f���p�[�c�̕`��
	for (int nCnt = 0; nCnt < TUTOMODEL; nCnt++)
	{
		// �S���f���`��
		m_pModel[nCnt]->Draw();
	}
}
