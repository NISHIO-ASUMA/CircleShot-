//====================================
//
// �G�̏�ԊǗ����� [ enemystate.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _ENEMYSTATE_H_ // ���̃}�N����`������ĂȂ�������
#define _ENEMYSTATE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "state.h"
#include "enemy.h"

//**************************
// �G�̏�ԊǗ����N���X
//**************************
class CEnemyStateBase :public CStateBase
{
public:
	//***************************
	// ��ԊǗ�ID�񋓌^
	//***************************
	enum ID
	{
		ID_NONE, // �ݒ�Ȃ�
		ID_FALL, // �������
		ID_MOVE, // �ړ�
		ID_DEATH,// ���S
		ID_MAX
	};

	CEnemyStateBase();
	~CEnemyStateBase();

	void SetOwner(CEnemy* pEnemy) { m_pEnemy = pEnemy; } // �|�C���^�Z�b�g

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	virtual void OnStart() {}

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	virtual void OnUpdate() {}

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	virtual void OnExit() {}

	// �Q�b�^�[
	int GetID() const override { return m_ID; }
	void SetID(ID id) { m_ID = id; }

protected:
	CEnemy* m_pEnemy;	// �G�̃|�C���^

private:
	ID m_ID;		// �񋓌^�̃����o�ϐ�
};

//**************************
// ������Ԏ��̊Ǘ�
//**************************
class CEnemyStateFall : public CEnemyStateBase
{
public:
	CEnemyStateFall();
	~CEnemyStateFall();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();

private:
	float m_fSpeedFall;	// �����X�s�[�h
};

//**************************
// �ړ���Ԏ��̊Ǘ�
//**************************
class CEnemyStateMove : public CEnemyStateBase
{
public:
	CEnemyStateMove();
	~CEnemyStateMove();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();
};
#endif
