//====================================
//
// �u���b�N���� [ block.cpp ]
// Author: Asuma Nishio
//
//=====================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "block.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_size = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CBlock::~CBlock()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CBlock::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	// ���ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CBlock::Uninit(void)
{
	// �e�N���X�̏I��
	CObjectX::Uninit();
}
//===============================
// �X�V����
//===============================
void CBlock::Update(void)
{
	// ����
}
//===============================
// �`�揈��
//===============================
void CBlock::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}
//===============================
// ��������
//===============================
CBlock* CBlock::Create(const char* pFileName, D3DXVECTOR3 pos,D3DXVECTOR3 rot,float fSize)
{
	// �C���X�^���X�𐶐�
	CBlock* pBlock = new CBlock;

	// nullptr��������
	if (pBlock == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pBlock->SetFilePass(pFileName);
	pBlock->SetPos(pos);
	pBlock->SetRot(rot);
	pBlock->m_size = fSize;

	// �^�C�v�w��
	pBlock->SetObjType(TYPE_BLOCK);

	// �������Ɏ��s������
	if (FAILED(pBlock->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �����|�C���^��Ԃ�
	return pBlock;
}