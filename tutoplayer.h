//====================================================
//
// �`���[�g���A���v���C���[���� [ tutoplayer.h ]
// Author: Asuma Nishio
//
//====================================================

#ifndef _TUTOPLAYER_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTOPLAYER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

#if 0
//********************************
// �C���N���[�h�t�@�C���錾
//********************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// �O���錾
//********************************
class CShadowS;
class CStateMachine;
class CPlayerStateBase;

//****************************************
// �`���[�g���A���v���C���[�N���X���`
//****************************************
class CTutoPlayer : public CObject
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
		PLAYERMOTION_JUMPATTACK,	// �W�����v�U��
		PLAYERMOTION_DAMAGE,		// �_���[�W
		PLAYERMOTION_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CTutoPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTutoPlayer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	// �ÓI�����o�֐�
	static CTutoPlayer* Create(D3DXVECTOR3 pos, const int nIdx, const char* pFileName);
	static CTutoPlayer* GetIdxPlayer(int Idx);

private:
	static inline constexpr int TUTOMODEL = 19; // �K�w�\�����f����

	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;  // �ړI�p

	D3DXVECTOR3 m_pos;		// �K�w�\���ݒ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X

	CModel* m_apModel[TUTOMODEL]; // �g�����f���̃|�C���^
	CMotion* m_pMotion;		// ���[�V�����̃|�C���^

	int m_nIdxPlayer;		// �v���C���[�̎��ʔԍ�
	const char* m_pFilename; // �ǂݍ��ރt�@�C����

	CShadowS* m_pShadowS;	// �X�e���V���V���h�E�N���X�|�C���^
	CStateMachine* m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^

	int m_type;				// ���[�V�����̎�ޕϐ�
	int m_nNumAll;			// ���f������
	int m_State;			// ��ԊǗ��J�E���^�[
	int m_nIdxTexture;		// �e�N�X�`��ID
	int m_nIdxPlayer;		// �v���C���[�̎��ʔԍ�

	bool m_isLanding;		// ���n����
	bool m_isJump;			// �W�����v����
	bool m_isMoving;		// �ړ��L�[����
	bool m_isAttack;		// �U������
	bool m_isShadow;
	bool m_isStateSynchro;

	float m_fAngle;			// ���݂̊p�x
	float m_fValue;

	const char* m_pFilename; // �ǂݍ��ރt�@�C����
};
#endif

#endif