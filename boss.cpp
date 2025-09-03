//====================================
//
// �{�X���� [ boss.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "boss.h"
#include "debugproc.h"
#include "manager.h"
#include "parameter.h"
#include "result.h"
#include <ctime>
#include "meshimpact.h"
#include "particle.h"
#include "bossstate.h"
#include "state.h"
#include "attacksign.h"
#include "player.h"
#include "effect.h"
#include "sound.h"

//****************************
// ���O���
//****************************
namespace BOSSINFO
{
	constexpr float HITRANGE = 12.0f; // �R���W�����T�C�Y
	constexpr int COOLTIME = 60;	  // �����N�[���^�C��
}

//****************************
// �ÓI�����o�ϐ��錾
//****************************
bool CBoss::m_isdaeth = false;		// ���S�t���O

//====================================
// �I�[�o�[���[�h�R���X�g���N�^
//====================================
CBoss::CBoss(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_WeekPointPos = VECTOR3_NULL;

	m_pMotion = nullptr;
	m_pParam = nullptr;
	m_pState = nullptr;

	m_type = NULL;
	m_nCoolTime = NULL;
	m_fWeekSize = NULL;
	m_fSize = NULL;

	m_mtxworld = {};

	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_isEvent = false;
	m_nCurrentMotion = PATTERN_NONE;
}
//====================================
// �f�X�g���N�^
//====================================
CBoss::~CBoss()
{
	// ����
}
//====================================
// ��������
//====================================
CBoss* CBoss::Create(D3DXVECTOR3 pos,float fSize,int nLife)
{
	// �C���X�^���X����
	CBoss* pBoss = new CBoss;

	// �������s��
	if (pBoss == nullptr) return nullptr;

	// �I�u�W�F�N�g�Z�b�g
	pBoss->m_pos = pos;
	pBoss->m_fSize = fSize;

	// ���������s��
	if (FAILED(pBoss->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �p�����[�^�[�|�C���^����
	pBoss->m_pParam = new CParameter;

	// �̗̓p�����[�^
	if (pBoss->m_pParam != nullptr)
	{
		pBoss->m_pParam->SetMaxHp(nLife);
		pBoss->m_pParam->SetHp(nLife);
	}

	// �|�C���^��Ԃ�
	return pBoss;
}
//=========================================
// ���f���̓��蕔���p�[�c�̎擾�֐�
//=========================================
CModel* CBoss::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// �{�X�������Ă��郂�f���̐��̒�����T��
	for (int nModel = 0; nModel < NUMMODELS; nModel++)
	{
		// ���f�������� ���� �擾���������ƈ�v���Ă�����
		if (m_pModel[nModel] && m_pModel[nModel]->GetPartType() == modelpart)
		{
			// �Y�����f����idx�ԍ��̃��f����Ԃ�
			return m_pModel[nModel];
		}
	}

	// �Y���Ȃ��̏ꍇ
	return nullptr;
}
//====================================
// ����������
//====================================
HRESULT CBoss::Init(void)
{
	// �t���O��������
	m_isdaeth = false;

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_BOSS);

	// �^�C�v���
	m_type = CBoss::TYPE_MAX;

	// �����N�[���^�C����ݒ�
	m_nCoolTime = BOSSINFO::COOLTIME;

	// ���[�V�����̓ǂݍ���
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\Bossmotion.txt", NUMMODELS, m_pModel, CBoss::TYPE_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(m_type);

	// �X�e�[�g����
	m_pState = new CStateMachine;

	// ������Ԃ��Z�b�g
	ChangeState(new CBossStateNeutral(120), CBossStateBace::ID_NEUTRAL);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//====================================
// �I������
//====================================
void CBoss::Uninit(void)
{
	// ���f�������̔j��
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_pModel[nCnt] != nullptr)
		{
			// �I������
			m_pModel[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_pModel[nCnt];

			// nullptr�ɂ���
			m_pModel[nCnt] = nullptr;
		}
	}

	// nullptr�`�F�b�N
	if (m_pMotion != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pMotion;

		// nullptr�ɂ���
		m_pMotion = nullptr;
	}

	// nullptr�`�F�b�N
	if (m_pParam != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pParam;

		// nullptr�ɂ���
		m_pParam = nullptr;
	}

	// nullptr�`�F�b�N
	if (m_pState != nullptr)
	{
		// �I������
		m_pState->OnExit();

		// �|�C���^�̔j��
		delete m_pState;

		// null������
		m_pState = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//====================================
// �X�V����
//====================================
void CBoss::Update(void)
{
	// ����ł�����
	if (m_isdaeth) return;

	// ���Z
	DecCoolTime();

	// null�`�F�b�N
	if (m_pState != nullptr)
	{
		// �X�e�[�g�X�V
		m_pState->Update();
	}

	//==========================
	// ��ڂ̎�_�p�[�c���擾
	//==========================
	CModel* pWeakHead = GetModelPartType(CModel::PARTTYPE_HEAD);

	// ��_�p�[�c�̃��[���h���W���擾
	D3DXMATRIX mtx = pWeakHead->GetMtxWorld();

	// ��_���W��ݒ�
	D3DXVECTOR3 weakPos(mtx._41, mtx._42 + 40.0f, mtx._43);

	// �G�t�F�N�g
	CEffect::Create(weakPos, COLOR_RED, VECTOR3_NULL, 50, 60.0f);

	// ���[�V�����S�̍X�V
	m_pMotion->Update(m_pModel, NUMMODELS);
}
//====================================
// �`�揈��
//====================================
void CBoss::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// �S���f���p�[�c�̕`��
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		// �S���f���`��
		m_pModel[nCnt]->Draw();
	}

	CDebugproc::Print("�{�X���W [ %.2f ,%.2f , %.2f]", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(0, 40);

	CDebugproc::Print("�{�X���[�V������ { %d }", m_type);
	CDebugproc::Draw(0, 180);

	CDebugproc::Print("�{�X�E����W { %.2f,%.2f,%.2f }", GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._41, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._42, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._43);
	CDebugproc::Draw(0, 300);

	CDebugproc::Print("�{�X�̗� { %d }", m_pParam->GetHp());
	CDebugproc::Draw(0, 400);

	CDebugproc::Print("�{�X�N�[���^�C�� { %d }",m_nCoolTime);
	CDebugproc::Draw(1080, 400);

	// �f�o�b�O�t�H���g
	m_pMotion->Debug();
}
//====================================
// �E��ƃv���C���[�̓����蔻��
//====================================
bool CBoss::CollisionRightHand(D3DXVECTOR3* pPos)
{
	// �����t���O���쐬
	static bool isCreate = false;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// ���t���[����
	if (m_pMotion->CheckFrame(25, 25, PATTERN_HAND) && !isCreate)
	{
		// �Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// �U���T�C���𐶐�
		CAttackSign::Create();

		// �����t���O��L����
		isCreate = true;
	}
	else
	{
		// �t���[���O�Ȃ烊�Z�b�g
		isCreate = false;
	}

	// ���t���[����
	if (m_pMotion->CheckFrame(100, 140, PATTERN_HAND) && m_isdaeth == false)
	{
		// ���f���̃p�[�c�擾
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // �E��

		// null��������
		if (!pRightHand) return false;

		// �E��̃��[���h�}�g���b�N�X���擾
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// �����v�Z
		D3DXVECTOR3 diff = *pPos - D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// �v�Z���������̒����擾
		float fDist = D3DXVec3Length(&diff);

		// ������Ԃ�
		return fDist <= (BOSSINFO::HITRANGE * BOSSINFO::HITRANGE);
	}
	else
	{
		// ������Ȃ��Ƃ�
		return false;
	}
}
//====================================
// �C���p�N�g���[�V�������̓����蔻��
//====================================
bool CBoss::CollisionImpactScal(D3DXVECTOR3* pPos)
{
	// ���f���̃p�[�c�擾
	CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // �E��

	// null��������
	if (!pRightHand) return false;

	// ���f���̃p�[�c�擾
	CModel* pLeftHand = GetModelPartType(CModel::PARTTYPE_LEFT_HAND); // ����

	// null��������
	if (!pLeftHand) return false;

	// ���f���̃p�[�c�擾
	CModel* pHead = GetModelPartType(CModel::PARTTYPE_HEAD); // ��

	// null��������
	if (!pHead) return false;

	// ��̃��[���h�}�g���b�N�X���擾
	D3DXMATRIX mtxRight = pRightHand->GetMtxWorld();
	D3DXMATRIX mtxLeft = pLeftHand->GetMtxWorld();

	// ���̃��[���h�}�g���b�N�X
	D3DXMATRIX mtxHead = pHead->GetMtxWorld();

	// �����t���O���쐬
	static bool isCreate = false;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// ���t���[����
	if (m_pMotion->CheckFrame(40, 40, PATTERN_IMPACT) && !isCreate)
	{
		// �Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// �U���T�C���𐶐�
		CAttackSign::Create();

		// �����t���O��L����
		isCreate = true;
	}
	else
	{
		// �t���[���O�Ȃ烊�Z�b�g
		isCreate = false;
	}

	// ���t���[����
	if (m_pMotion->CheckFrame(120, 160, PATTERN_IMPACT) && !m_isdaeth)
	{
		// ���W���i�[
		D3DXVECTOR3 posRight(mtxRight._41, mtxRight._42, mtxRight._43);
		D3DXVECTOR3 posLeft(mtxLeft._41, mtxLeft._42, mtxLeft._43);

		// ����̍��W�̒��S�_���v�Z
		D3DXVECTOR3 HandCenterPos = (posRight + posLeft) * 0.5f;

		// �v���C���[�Ƃ̋����𑪒�
		const float fHitRadius = 22.0f * BOSSINFO::HITRANGE; // ���蔼�a

		// �����v�Z�p
		D3DXVECTOR3 diff = VECTOR3_NULL;

		// �E��Ƃ̍���
		diff = posRight - *pPos;

		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			return true;
		}

		// ����Ƃ̍���
		diff = posLeft - *pPos;

		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			return true;
		}
	}

	return false;
}

//====================================
// �q�b�g����
//====================================
void CBoss::Hit(int nDamage,D3DXVECTOR3 HitPos)
{
	// �t���O�������Ă�����
	if (m_isdaeth) return;

	// �����̃_���[�W���i�[
	int realDamage = nDamage;

	//==========================
	// ��ڂ̎�_�p�[�c���擾
	//==========================
	CModel* pWeakHead = GetModelPartType(CModel::PARTTYPE_HEAD);

	// null����Ȃ�������
	if (pWeakHead)
	{
		// ��_�p�[�c�̃��[���h���W���擾
		D3DXMATRIX mtx = pWeakHead->GetMtxWorld();

		// ��_���W��ݒ�
		D3DXVECTOR3 weakPos(mtx._41, mtx._42, mtx._43 - 20.0f);

		// �q�b�g���W�Ƃ̋����𑪒�
		D3DXVECTOR3 diff = HitPos - weakPos;
		float fDist = D3DXVec3Length(&diff);

		// ����͈͓��Ȃ�
		if (fDist <= WEEKPOINTSIZE)
		{
			// �_���[�W3�{�ɂ���
			realDamage = nDamage * 3;
		}
	}

	// HP�����Z
	int nHp = m_pParam->GetHp();
	nHp -= realDamage;

	// 0�ȉ��Ȃ�
	if (nHp <= 0)
	{
		// ���S����
		m_isdaeth = true;

		// ���S���[�V�����Ăяo��

	}
	else
	{
		// ���ݑ̗͂�ݒ�
		m_pParam->SetHp(nHp);

		// �ő�HP�̔��������������X�e�[�g�ύX
		int nMaxHp = m_pParam->GetMaxHp();

		if (nHp <= nMaxHp * 0.5f)
		{
			// �t���O�����g�p�Ȃ�
			if (!m_isEvent)
			{
				// �t���O��L����
				m_isEvent = true;

				// �C�x���g��Ԃֈڍs
				ChangeState(new CBossStateEvent(), CBossStateBace::ID_EVENT);

				return;
			}
		}
	}
}
//====================================
// ��ԕύX����
//====================================
void CBoss::ChangeState(CBossStateBace* pNewState, int Id)
{
	// �������g���Z�b�g����
	pNewState->SetOwner(this);

	// ��Ԃ�ύX����
	m_pState->ChangeState(pNewState);
}
//====================================
// ��������]�����鏈��
//====================================
void CBoss::RollToPlayer(void)
{
	// �v���C���[�̎擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);

	// null�Ȃ�
	if (pPlayer == nullptr) return;

	// �v���C���[�̍��W���擾
	D3DXVECTOR3 pPos = pPlayer->GetPos();

	// �{�X����v���C���[�Ɉ�{�̃x�N�g���𐶐�����
	D3DXVECTOR3 VecPlayer = m_pos - pPos;

	// ���������̊p�x�����߂�
	float angle = atan2f(VecPlayer.x, VecPlayer.z);

	// �v�Z�����p�x���Z�b�g
	m_rot.y = angle;
}