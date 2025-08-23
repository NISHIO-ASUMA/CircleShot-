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
	// �����o���AUI�𐶐�
	m_pBarrierUI = CBarrierDurability::Create
	(
		D3DXVECTOR3(100, 50, 0),  // �ʒu
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		32.0f, 
		32.0f,
		CBarrierDurability::GUARD_FRAME
	);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CBarrierManager::Uninit(void)
{
	// �e��I������
}
//============================
// �X�V����
//============================
void CBarrierManager::Update(void)
{
	// null����Ȃ�������
	if (m_pBarrierUI)
	{
		// �ϋv�l�ɉ����ĕύX
		switch (m_nBarrierNum)
		{
		case CBarrierDurability::GUARD_FRAME:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_FRAME); 
			break;

		case CBarrierDurability::GUARD_FIRST:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_FIRST); 
			break;

		case CBarrierDurability::GUARD_SECOND:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_SECOND); 
			break;

		case CBarrierDurability::GUARD_THIRD:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_THIRD); 
			break;
		}
	}
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
//============================
// �o���A���Z����
//============================
void CBarrierManager::DamageBarrier(int nValue)
{
	// �ϋv�l�����炷
	m_nBarrierNum -= nValue;

	// 0�ȉ��Ȃ�
	if (m_nBarrierNum < 0) m_nBarrierNum = 0; // �ŏ�����
}
