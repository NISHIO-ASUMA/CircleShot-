//=============================================
//
// �v���C���[��ԊǗ����� [ playerstate.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "playerstate.h"
#include "state.h"
#include "manager.h"
#include "gamemanager.h"
#include "parameter.h"

//******************************
// �萔�錾
//******************************
constexpr int DAMAGECOUNT = 60;	// �ő�X�e�[�g�J�E���g

//==================================
// �v���C���[��ԃR���X�g���N�^
//==================================
CPlayerStateBase::CPlayerStateBase()
{
	// �l�̃N���A
	m_pPlayer = nullptr;
	m_ID = ID_NEUTRAL;
}
//==================================
// �v���C���[��ԃf�X�g���N�^
//==================================
CPlayerStateBase::~CPlayerStateBase()
{
	// ����
}


//==================================
// �ҋ@��Ԏ��R���X�g���N�^
//==================================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// �Z�b�g
	SetID(ID_NEUTRAL);
}
//==================================
// �ҋ@��Ԏ��f�X�g���N�^
//==================================
CPlayerStateNeutral::~CPlayerStateNeutral()
{
	// ����
}
//==================================
// �ҋ@��ԊJ�n�֐�
//==================================
void CPlayerStateNeutral::OnStart()
{		
	// �j���[�g�������[�V�����ɐݒ�
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_NEUTRAL,true,10, false);
}
//==================================
// �ҋ@��ԍX�V�֐�
//==================================
void CPlayerStateNeutral::OnUpdate()
{
	// �L�[���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// �ړ����͂�����Έړ���Ԃ�
	if ((m_pPlayer->isMoveInputKey(pInput) || m_pPlayer->isMovePadButton(pPad)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// ��ԕύX
		m_pPlayer->ChangeState(new CPlayerStateMove,ID_MOVE);

		// �����ŏ�����Ԃ�
		return;
	}

	// �U���L�[���͎�
	if ((pInput->GetPress(DIK_RETURN) || pPad->GetPress(CJoyPad::JOYKEY_X)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE) 
	{
		// �X�e�[�g�ύX
		m_pPlayer->ChangeState(new CPlayerStateAction,ID_ACTION);

		// �����ŏ�����Ԃ�
		return;
	}

	// Space�L�[ �������� Pad��A�L�[
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// �X�e�[�g�ύX
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// �����ŏ�����Ԃ�
		return;
	}
}
//==================================
// �ҋ@��Ԏ��I���֐�
//==================================
void CPlayerStateNeutral::OnExit()
{
	// ����
}


//==================================
// �R���X�g���N�^
//==================================
CPlayerStateAction::CPlayerStateAction()
{
	// �Z�b�g
	SetID(ID_ACTION);
}
//==================================
// �f�X�g���N�^
//==================================
CPlayerStateAction::~CPlayerStateAction()
{
	// ����
}
//==================================
// �U����ԊJ�n�֐�
//==================================
void CPlayerStateAction::OnStart()
{
	// �U�����[�V�����ɕύX
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_ACTION);
}
//==================================
// �U����ԍX�V�֐�
//==================================
void CPlayerStateAction::OnUpdate()
{
	// ���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad * pPad = CManager::GetJoyPad();

	// �d��
	m_pPlayer->GravityScal();

	// ����̈ʒu�擾
	CModel* pModelWeapon = m_pPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// null��������
	if (!pModelWeapon) return;

	// �r�̃��[���h�}�g���b�N�X���擾
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	// �v���C���[�ƃ{�X�ԂŃx�N�g������
	D3DXVECTOR3 VecBoss = m_pPlayer->VecToBoss(m_pPlayer->GetPos());

	// �U���X�V
	m_pPlayer->UpdateAction(pInput, mtxWorld, VecBoss, pPad);
}
//==================================
// �U����ԏI���֐�
//==================================
void CPlayerStateAction::OnExit()
{
	// ����
}


//==================================
// �ړ���ԃR���X�g���N�^
//==================================
CPlayerStateMove::CPlayerStateMove()
{
	// �Z�b�g
	SetID(ID_MOVE);
}
//==================================
// �ړ���ԃf�X�g���N�^
//==================================
CPlayerStateMove::~CPlayerStateMove()
{
	// ����
}
//==================================
// �ړ���ԊJ�n�֐�
//==================================
void CPlayerStateMove::OnStart()
{
	// ����
}
//==================================
// �ړ���ԍX�V�֐�
//==================================
void CPlayerStateMove::OnUpdate()
{
	// �L�[���͂��擾	
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// �V�����_�[���W�̎擾
	D3DXVECTOR3 MeshPos = CGameManager::GetCylinder()->GetPos();

	// �ړ��������s
	m_pPlayer->UpdateMove(MeshPos, pInput, pPad);

	// �L�[���͂�����
	if (!m_pPlayer->isMoveInputKey(pInput) && !m_pPlayer->isMovePadButton(pPad)
		&& m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// �j���[�g�����ɑJ��
		m_pPlayer->ChangeState(new CPlayerStateNeutral, ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}

	// �W�����v�L�[���͎��ɃX�e�[�g�ύX
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE		   &&
		!m_pPlayer->IsJumping())
	{
		// �W�����v�ɑJ��
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// �����ŏ�����Ԃ�
		return;
	}
}
//==================================
// �ړ���ԏI���֐�
//==================================
void CPlayerStateMove::OnExit()
{
	// ����
}

//==================================
// �_���[�W��ԃR���X�g���N�^
//==================================
CPlayerStateDamage::CPlayerStateDamage(int nDamage)
{
	// id�ύX
	SetID(ID_DAMAGE);

	// �l�̃N���A
	m_nStateCount = NULL;
	m_nDamage = nDamage;
}
//==================================
// �_���[�W��ԃf�X�g���N�^
//==================================
CPlayerStateDamage::~CPlayerStateDamage()
{
	// ����
}
//==================================
// �_���[�W��ԊJ�n�֐�
//==================================
void CPlayerStateDamage::OnStart()
{
	// ��̖ڂ̃v���C���[�̎�
	if (m_pPlayer->GetPlayerIndex() == 0)
	{
		// ���[�V�����Z�b�g
		m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_DAMAGE, false, 0, false);

		// �̗͂����炷
		m_pPlayer->HitDamage(m_nDamage);
	}

	// ��ԕύX
	m_nStateCount = DAMAGECOUNT;
}
//==================================
// �_���[�W��ԍX�V�֐�
//==================================
void CPlayerStateDamage::OnUpdate()
{
	// �󒆎�,�d��
	m_pPlayer->GravityScal();

	// �ʒu�X�V
	m_pPlayer->AddMove();

	// ��ԊǗ��J�E���^�[���f�N�������g
	m_nStateCount--;

	if (m_nStateCount <= NULL)
	{
		// �J�E���g��ύX
		m_nStateCount = DAMAGECOUNT; 

		// ��ԕύX
		m_pPlayer->ChangeState(new CPlayerStateNeutral(), ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}
}
//==================================
// �_���[�W��ԍX�V�֐�
//==================================
void CPlayerStateDamage::OnExit()
{
	// ����
}


//==================================
// �W�����v��Ԏ��R���X�^���N�^
//==================================
CPlayerStateJump::CPlayerStateJump()
{
	// ID���Z�b�g
	SetID(ID_JUMP);
}
//==================================
// �W�����v��Ԏ��f�X�g���N�^
//==================================
CPlayerStateJump::~CPlayerStateJump()
{
	// ����
}
//==================================
// �W�����v��Ԏ��J�n�֐�
//==================================
void CPlayerStateJump::OnStart()
{
	// �W�����v�J�n
	m_pPlayer->StartJump();

	// �W�����v���[�V�����ɕύX
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_JUMP);
}
//==================================
// �W�����v��Ԏ��X�V�֐�
//==================================
void CPlayerStateJump::OnUpdate()
{
	// ���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// ����̈ʒu�擾
	CModel* pModelWeapon = m_pPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// null��������
	if (!pModelWeapon) return;

	// �r�̃��[���h�}�g���b�N�X���擾
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	// �v���C���[�ƃ{�X�ԂŃx�N�g������
	D3DXVECTOR3 VecBoss = m_pPlayer->VecToBoss(m_pPlayer->GetPos());

	// �W�����v�X�V�֐�
	m_pPlayer->UpdateJumpAction(pInput, mtxWorld, VecBoss, pPad);
}
//==================================
// �W�����v��Ԏ��I���֐�
//==================================
void CPlayerStateJump::OnExit()
{
	// �W�����v�𖢎g�p
	m_pPlayer->SetJump(false);

	// ���n�𖢎g�p
	m_pPlayer->SetLanding(true);
}
