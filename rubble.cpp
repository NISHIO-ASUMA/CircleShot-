//========================================
//
// ���I�I�u�W�F�N�g���� [ rubble.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "rubble.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CRubble::CRubble(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
}
//================================
// �f�X�g���N�^
//================================
CRubble::~CRubble()
{
	// ����
}
//================================
// ����������
//================================
HRESULT CRubble::Init(void)
{
	// �e�N���X����������
	CObjectX::Init();

	// �I�u�W�F�N�g�̎�ޒ�`
	SetObjType(CObject::TYPE_BLOCK);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CRubble::Uninit(void)
{
	// �e�N���X�I������
	CObjectX::Uninit();
}
//================================
// �X�V����
//================================
void CRubble::Update(void)
{
	// �ꎞ�ۗ�
}
//================================
// �`�揈��
//================================
void CRubble::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}
//================================
// ��������
//================================
CRubble* CRubble::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// �C���X�^���X����
	CRubble* pRubble = new CRubble;

	// ����null��������
	if (pRubble == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pRubble->SetFilePass(pFilename);
	pRubble->SetPos(pos);
	pRubble->SetRot(rot);

	// ���������s��
	if (FAILED(pRubble->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pRubble;
}
