//====================================
//
// �{�X���� [ boss.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BOSS_H_ // ���̃}�N����`������ĂȂ�������
#define _BOSS_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// �O���錾
//**********************
class CParameter;
class CStateMachine;
class CBossStateBace;

//**********************
// �{�X�N���X���`
//**********************
class CBoss : public CObject
{
public:
	//***************************
	// ���[�V�����񋓌^�錾
	//***************************
	enum TYPE
	{
		TYPE_NEUTRAL = 0,	// �j���[�g����
		TYPE_ACTION,		// �r�U��
		TYPE_IMPACT,		// �@�����Ռ��g
		TYPE_MAX
	};

	//***************************
	// �s���p�^�[���񋓌^
	//***************************
	enum ATTACKPATTERN
	{
		PATTERN_NONE, // �����s�����Ă��Ȃ�
		PATTERN_HAND, // ����
		PATTERN_IMPACT, // �@����
		PATTERN_CIRCLE, // �U��񂵍U��
		PATTERN_DEATH,	// ���S���[�V����
		PATTERN_MAX
	};

	CBoss(int nPriority = static_cast<int>(CObject::PRIORITY::BOSS));
	~CBoss();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBoss* Create(D3DXVECTOR3 pos, float fSize,int nLife);

	D3DXVECTOR3 GetPos(void) { return m_pos;}
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	CParameter* GetParam(void) { return m_pParam; }

	float GetSize(void) { return m_fSize; }

	bool CollisionRightHand(D3DXVECTOR3* pPos);
	bool CollisionImpactScal(D3DXVECTOR3* pPos);

	static bool IsDaeth(void) { return m_isdaeth;}

	CModel*GetModelPartType(CModel::PARTTYPE modelpart);

	void Hit(int nDamage);

	void SetCoolTime(int nCooltime) { m_nCoolTime = nCooltime; }
	void DecCoolTime(void) { if (m_nCoolTime > 0) m_nCoolTime--; }
	int GetCoolTime(void) const { return m_nCoolTime; }

	CMotion* GetMotion(void) { return m_pMotion; }

	void ChangeState(CBossStateBace* pNewState, int Id); // �X�e�[�g�ύX

	void RollToPlayer(void);

private:

	static constexpr int NUMMODELS = 21; // �g�����f����

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;	// �}�g���b�N�X

	CModel* m_pModel[NUMMODELS]; // ���f���̃|�C���^
	CMotion* m_pMotion;		// ���[�V�����|�C���^
	CParameter* m_pParam;	// �p�����[�^�[�|�C���^
	CStateMachine* m_pState; // �X�e�[�g�|�C���^

	int m_type;			   // ���[�V�����̎�ޕϐ�
	float m_fSize;		   // �T�C�Y

	int m_nCoolTime;	// �N�[���^�C��
	int m_nCurrentMotion;
	bool m_isAttacked;  // �U�����Ă��邩
	static bool m_isdaeth;
};

#endif
