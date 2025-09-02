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
#include "manager.h"
#include "player.h"

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
		int attackType = rand() % 4;

		switch (attackType)
		{
		case CBoss::PATTERN_HAND:  // ����
			m_pBoss->ChangeState(new CBosshandAttack(), ID_ACTION);
			return;

		case CBoss::PATTERN_IMPACT: // �@����
			m_pBoss->ChangeState(new CBossimpactAttack(), ID_ACTION);
			return;

		case CBoss::PATTERN_OBSTRACT: // �@����
			m_pBoss->ChangeState(new CBossStateEvent(), ID_EVENT);
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


//===========================
// �R���X�g���N�^
//===========================
CBossStateEvent::CBossStateEvent()
{
	// ID�Z�b�g
	SetID(ID_EVENT);
}
//===========================
// �f�X�g���N�^
//===========================
CBossStateEvent::~CBossStateEvent()
{
	//����
}
//===========================
// �C�x���g��ԊJ�n�֐�
//==========================
void CBossStateEvent::OnStart(void)
{
	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::PATTERN_OBSTRACT);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(245);

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr) return;

	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (pPlayer == nullptr) return;

	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	// ��������ƍ���
	float backDistance = 550.0f;
	float heightOffset = 150.0f;

	// �v���C���[�̌����̋t�������擾
	float rotY = pPlayer->GetRotDest().y;
	D3DXVECTOR3 backwardVec = D3DXVECTOR3(-sinf(rotY), 0.0f, -cosf(rotY));

	// �J�����ʒu
	D3DXVECTOR3 camPos = playerPos + backwardVec * backDistance;
	camPos.y += heightOffset; // �v���C���[��菭���キ�炢

	// ����
	D3DXVECTOR3 targetPos = playerPos + D3DXVECTOR3(0.0f, 250.0f, 0.0f); // Y��傫�����Č��グ��

	// �J�����`�F���W
	pCamera->SetCameraMode(pCamera->MODE_EVENT);

	// �C�x���g�J�����J�n
	pCamera->StartEventCamera(camPos, targetPos, 250);

	// �J�����̐U��
	pCamera->ShakeCamera(240);
}
//===========================
// �C�x���g��ԍX�V�֐�
//==========================
void CBossStateEvent::OnUpdate(void)
{
	// ���݂̃N�[���^�C���擾
	int nCooltime = m_pBoss->GetCoolTime();

	// �N�[���^�C�����Ȃ��Ȃ�����
	if (nCooltime <= 0)
	{
		// ��ԕύX
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}
}
//===========================
// �C�x���g��ԏI���֐�
//==========================
void CBossStateEvent::OnExit(void)
{

}
