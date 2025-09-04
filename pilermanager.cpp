//===============================================
//
// �~���U���Ǘ����� [ pilermanager.cpp ]
// Author : Asuma Nishio
//
//===============================================

//**********************************
// �C���N���[�h�t�@�C���錾
//**********************************
#include "pilermanager.h"
#include "meshpiler.h"
#include "meshcircle.h"
#include "effectsmoke.h"
#include "manager.h"

//**********************************
// ���O���
//**********************************
namespace PILERMANAGERINFO
{
	constexpr int MAX_ACTIVETIME = 420;	// �ő�J�E���g
	constexpr int SIRCLECOUNT = 20;		// �~�`�����J�E���g
	constexpr int PILERCOUNT = 25;		// �~�������J�E���g
}
//===============================
// �R���X�g���N�^
//===============================
CPilerManager::CPilerManager()
{
	// �l�̃N���A
	m_nTimer = NULL;
	m_nCount = NULL;
	m_State = STATE_IDLE;
	m_LastCirclePos = VECTOR3_NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CPilerManager::~CPilerManager()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CPilerManager::Init(void)
{
	// �ϐ��̏�����
	m_nTimer = NULL;
	m_nCount = NULL;
	m_State = STATE_IDLE;
	m_nActiveTime = PILERMANAGERINFO::MAX_ACTIVETIME;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CPilerManager::Uninit(void)
{
	// ����
}
//===============================
// �X�V����
//===============================
void CPilerManager::Update(D3DXVECTOR3* DestPos)
{
	// �C�x���g�J�������[�h�Ȃ�
	if (CManager::GetCamera()->GetMode() == CManager::GetCamera()->MODE_EVENT) return;

	// �A�N�e�B�u�^�C�������Z
	m_nActiveTime--;

	// 0�ȉ��ɂȂ�����
	if (m_nActiveTime <= 0)
	{
		// �����_���l��ݒ�
		int nNumActive = (rand() % 3) + 4;

		switch (m_State)
		{
		case STATE_IDLE:	// �ҋ@��
		
			// �J�E���g�����Z
			m_nTimer++;

			// ��������
			if (m_nTimer > PILERMANAGERINFO::SIRCLECOUNT)
			{
				// �T�[�N���o��
				CMeshCircle::Create(*DestPos, 60.0f);

				// �o�������ʒu��ۑ�
				m_LastCirclePos = *DestPos;

				// �^�C�������Z�b�g
				m_nTimer = 0;

				// ��Ԃ�ύX
				m_State = STATE_WAIT_PILER;
			}
			break;
		

		case STATE_WAIT_PILER:	

			// �^�C�������Z
			m_nTimer++;

			// ��������
			if (m_nTimer > PILERMANAGERINFO::PILERCOUNT)
			{
				// �~���o��
				CMeshPiler::Create(m_LastCirclePos, 15.0f);

				// �o���񐔂𑝂₷
				m_nCount++;	

				// �^�C���J�E���g��������
				m_nTimer = 0;

				if (m_nCount >= nNumActive)
				{
					// ��ԕύX
					m_State = STATE_COOLTIME;
				}
				else
				{
					// ��ԕύX
					m_State = STATE_IDLE;
				}
			}
			break;

		case STATE_COOLTIME:	// �N�[���^�C��

			// �J�E���g�����Z
			m_nTimer++;

			// 7�b��������
			if (m_nTimer > PILERMANAGERINFO::MAX_ACTIVETIME)
			{
				// ���Z�b�g���čĂъJ�n
				m_nTimer = 0;
				m_nCount = 0;
				m_State = STATE_IDLE;
				m_nActiveTime = PILERMANAGERINFO::MAX_ACTIVETIME;
			}
			break;
		}
	}
}