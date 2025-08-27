//============================================
//
// �A�C�e���Ǘ����� [ itemmanager.cpp ]
// Author : Asuma Nishio
// 
// TODO : �A�C�e���̐���,�Ǘ�������
//
//============================================

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "itemmanager.h"
#include "gamemanager.h"
#include "time.h"
#include "item.h"

//=================================
// �R���X�g���N�^
//=================================
CItemManager::CItemManager()
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CItemManager::~CItemManager()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CItemManager::Init(void)
{
	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CItemManager::Uninit(void)
{
	// �e��I������

}
//=================================
// �X�V����
//=================================
void CItemManager::Update(void)
{
	// �^�C�}�[���擾
	CTime* pTime = CGameManager::GetTime();

	if (pTime == nullptr) return;

	// �^�C�}�[���擾
	int NowTime = pTime->GetAllTime();

	static int lastSpawnTime = -1;

	// 5�b���Ƃɐ���
	if (NowTime % 5 == 0 && NowTime != lastSpawnTime)
	{
		// �����_������
		int nActivePos = rand() % 3;

		// �A�C�e������
		CItem::Create(m_ActivePointPos[nActivePos], VECTOR3_NULL, "data\\MODEL\\STAGEOBJ\\Guard000.x");

		lastSpawnTime = NowTime;
	}
}
