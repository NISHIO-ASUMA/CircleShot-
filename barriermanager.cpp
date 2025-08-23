//=====================================================
//
// �o���A�I�u�W�F�N�g�̊Ǘ����� [ barriermanager.cpp ]
// Author : Asuma Nishio
// 
// TODO : ������Q�[���}�l�[�W���[�Ŏ擾�ł���悤�ɂ��ă|�C���^��n��
//
//=====================================================

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "barriermanager.h"
#include "barrierdurability.h"

//*********************************
// ���O���
//*********************************
namespace BARRIERINFO
{
	inline constexpr int MAX_GUARD = 3;
};

//============================
// �R���X�g���N�^
//============================
CBarrierManager::CBarrierManager()
{
	// �l�̃N���A
	m_nBarrierNum = NULL;
	m_pBarrierUI = nullptr;
}
//============================
// �f�X�g���N�^
//============================
CBarrierManager::~CBarrierManager()
{
	// ����
}
//============================
// ����������
//============================
HRESULT CBarrierManager::Init(void)
{
	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CBarrierManager::Uninit(void)
{

}
//============================
// �X�V����
//============================
void CBarrierManager::Update(void)
{
	// UI����
}
//============================
// �o���A���Z����
//============================
void CBarrierManager::AddBarrier(int nValue)
{
	// ����l�ȏ�Ȃ�
	if (m_nBarrierNum >= BARRIERINFO::MAX_GUARD) return;

	// ���Z����
	m_nBarrierNum += nValue;

}
