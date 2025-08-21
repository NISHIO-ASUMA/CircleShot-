//====================================
//
// �v���C���[���� [ player.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PLAYER_H_ // ���̃}�N����`������ĂȂ�������
#define _PLAYER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// �O���錾
//**********************
class CShadow;
class CInputKeyboard;
class CJoyPad;
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CPlayerStateBase;

//*************************
// �v���C���[�N���X���`
//*************************
class CPlayer : public CObject
{
public:
	//***********************************
	// �v���C���[���s�����[�V�����񋓌^
	//***********************************
	enum PLAYERMOTION
	{
		PLAYERMOTION_NEUTRAL,		// �j���[�g����
		PLAYERMOTION_MOVE,			// �ړ�
		PLAYERMOTION_ACTION,		// �A�N�V����
		PLAYERMOTION_JUMP,			// �W�����v
		PLAYERMOTION_LANDING,		// ���n
		PLAYERMOTION_JUMPATTACK,	// SP�U��
		PLAYERMOTION_DAMAGE,		// ������΂�
		PLAYERMOTION_WAKEUP,		// �N���オ��
		PLAYERMOTION_MAX
	};

	CPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::PLAYER));
	~CPlayer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, const int nIdxParson,const char * pFilename); // ��������

	D3DXVECTOR3 GetPos(void) { return m_pos; } // ���݂̍��W���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; } // ���݂̊p�x���擾
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; } // �ړI�p���擾

	void SetRotDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
	bool IsJumping() { return m_isJump; } 	// �W�����v��Ԃ̊m�F
	void SetJump(bool isJump) { m_isJump = isJump; }
	void SetLanding(bool isLanding) { m_isLanding = isLanding; }

	static CPlayer* GetIdxPlayer(int Idx); // �C���f�b�N�X�ԍ��Ŏ擾
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	CModel* GetModelPartType(CModel::PARTTYPE modelpart);
	int GetType(void) { return m_type; }

	void ChangeState(CPlayerStateBase* pNewState,int Id); // �X�e�[�g�ύX
	CStateMachine* GetStateMachine(){return m_pStateMachine;}	// �v���C���[�̃X�e�[�g�}�V�����擾

	CMotion* GetMotion(void) { return m_pMotion; }
	CParameter* GetParameter(void) { return m_pParameter;}

	void UpdateAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestPos, CJoyPad* pPad); // �ʏ�U���X�V�֐�
	void UpdateMove(const D3DXVECTOR3 DestPos, CInputKeyboard* pInputKeyboard,CJoyPad * pPad);   // �ړ��X�V�֐�
	void UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad);

	void Collision(void);
	void AddMove(void) {m_pos += m_move;}

	void SetValue(float fValue) {m_fValue = fValue;}
	void JumpMove(void) { m_move.y = m_fValue; }

	D3DXVECTOR3 VecToBoss(const D3DXVECTOR3& pPos);

	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);
	bool isAttackeyPress(CInputKeyboard* pKeyInput);

	bool isLanding(void) { return m_isJump; }
	void InitPos(float fAngle);

	void StartJump(void);
	void GravityScal(void);

	static bool IsDeath(void) { return m_isDeath; }

	static inline constexpr int MAX_MODEL = 19; // �v���C���[�Ŏg�����f���̐�
	PLAYERMOTION GetNowMotion(void) const;

	void HitDamage(int nDamage);	// ���菈��

private:

	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;  // �ړI�p

	D3DXVECTOR3 m_pos;		// �K�w�\���ݒ���W
	D3DXVECTOR3 m_posOld;	// �ߋ��̍��W���
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X

	CModel* m_apModel[MAX_MODEL]; // �g�����f���̃|�C���^
	CMotion* m_pMotion;		// ���[�V�����̃|�C���^
	CShadow* m_pShadow;		// �e�N���X�̃|�C���^�ϐ�
	CParameter* m_pParameter; // �p�����[�^�[�N���X�|�C���^
	CShadowS* m_pShadowS;	// �X�e���V���V���h�E�N���X�|�C���^
	CStateMachine* m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^

	int m_type;				// ���[�V�����̎�ޕϐ�
	int m_nNumAll;		    // ���f������
	int m_State;			// ��ԊǗ��J�E���^�[
	int m_nIdxTexture;		// �e�N�X�`��ID

	bool m_isLanding;		// ���n����
	bool m_isJump;			// �W�����v����
	bool m_isMoving;		// �ړ��L�[����
	bool m_isAttack;		// �U������
	bool m_isShadow;
	bool m_isStateSynchro;
	static bool m_isDeath;

	bool m_isConectPad;

	float m_fAngle;			// ���݂̊p�x
	int m_nIdxPlayer;		// �v���C���[�̎��ʔԍ�

	const char* m_pFilename; // �ǂݍ��ރt�@�C����

	float m_fValue;

};

#endif