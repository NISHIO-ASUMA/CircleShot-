//====================================
//
// UI���� [ ui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "ui.h"
#include "texture.h"
#include "manager.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CUi::CUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTexIdxType = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CUi::~CUi()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CUi::Init(void)
{
	// �I�u�W�F�N�g�̏�����
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CUi::Uninit(void)
{
	// �I�u�W�F�N�g�̏I��
	CObject2D::Uninit();
}
//===============================
// �X�V����
//===============================
void CUi::Update(void)
{
	//// ���W�擾
	//D3DXVECTOR3 Pos = GetPos();

	//// 0.0f��菬�����ʒu�ɂ���
	//if (Pos.y <= 180.0f)
	//{
	//	Pos.y += 5.0f;
	//}

	//// ���W�Z�b�g
	//SetPos(Pos);

	//if (m_type == UITYPE_NONE)
	//{
	//	SetFlash(10, 20);
	//}

	// �I�u�W�F�N�g�̍X�V
	CObject2D::Update();
}
//===============================
// �`�揈��
//===============================
void CUi::Draw(void)
{
	// �J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	// �擾���s��
	if (pCamera == nullptr) return;

	// �t���O���Q�b�g����
	bool isKey = pCamera->GetIsRotation();

	if (!isKey)
	{
		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���Z�b�g
		CTexture* pTexture = CManager::GetTexture();

		// ���蓖��
		pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdxType));

		// �I�u�W�F�N�g�̕`��
		CObject2D::Draw();
	}
	else
	{
		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���Z�b�g
		CTexture* pTexture = CManager::GetTexture();

		// ���蓖��
		pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdxType));

		// �I�u�W�F�N�g�̕`��
		CObject2D::Draw();
	}
	
}
//===============================
// ��������
//===============================
CUi* CUi::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, const char* Filename, int nAnchorType)
{
	// �C���X�^���X����
	CUi* pUi = new CUi;

	// ���������s��
	if (FAILED(pUi->Init()))
	{
		// �|�C���^�̔j��
		delete pUi;

		// nullptr���
		pUi = nullptr;

		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pUi->SetPos(pos);
	pUi->SetSize(fWidth, fHeight);
	pUi->SetAnchor(nAnchorType);
	pUi->SetTexture(Filename);

	// pUi->m_type = nType;

	// �������ꂽ�|�C���^��Ԃ�
	return pUi;
}
//===============================
// �e�N�X�`���Z�b�g����
//===============================
void CUi::SetTexture(const char* pRegistername)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null����Ȃ�������
	if (pTexture != nullptr)
	{
		// �e�N�X�`���ݒ�
		m_nTexIdxType = pTexture->Register(pRegistername);
	}
}
