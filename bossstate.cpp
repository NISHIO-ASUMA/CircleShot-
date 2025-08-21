//=====================================
//
// �{�X��ԊǗ����� [ bossstate.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "bossstate.h"
#include "bossattackstate.h"

//===========================
// �R���X�g���N�^
//===========================
CBossStateBace::CBossStateBace()
{
	// �l�̃N���A
	m_ID = ID_NEUTRAL;
	m_pBoss = nullptr;
}
//===========================
// �f�X�g���N�^
//===========================
CBossStateBace::~CBossStateBace()
{
	// ����
}


//===========================
// �ҋ@��ԃR���X�g���N�^
//===========================
CBossStateNeutral::CBossStateNeutral(int nTime) : m_CoolTime(nTime), m_nCurrentState(0)
{
	// ID�Z�b�g
	SetID(ID_NEUTRAL);
}
//===========================
// �ҋ@��ԃf�X�g���N�^
//===========================
CBossStateNeutral::~CBossStateNeutral()
{
	// ����
}
//===========================
// �ҋ@��ԊJ�n����
//===========================
void CBossStateNeutral::OnStart(void)
{
	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL,false,0,false);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(m_CoolTime);
}
//===========================
// �ҋ@��ԍX�V����
//===========================
void CBossStateNeutral::OnUpdate(void)
{
	// ���Z
	m_pBoss->DecCoolTime();

	if (m_pBoss->GetCoolTime() <= 0)
	{
		// �����_���Ńp�^�[��������
		int attackType = rand() % CBoss::PATTERN_MAX;

		switch (attackType)
		{
		case CBoss::PATTERN_HAND:  // ����
			m_pBoss->ChangeState(new CBosshandAttack(), ID_ACTION);
			return;

		case CBoss::PATTERN_IMPACT: // �@����
			m_pBoss->ChangeState(new CBossimpactAttack(), ID_ACTION);
			return;
		}
	}
	else
	{
		// �N�[���^�C�����̓j���[�g�������[�V�����Đ�
		m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL, false, 0,false);
	}
}
//===========================
// �ҋ@��ԏI������
//===========================
void CBossStateNeutral::OnExit(void)
{
	// ����
}
