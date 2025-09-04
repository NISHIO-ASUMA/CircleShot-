//===============================================
//
// �~���U���Ǘ����� [ pilermanager.h ]
// Author : Asuma Nishio
//
//===============================================

#ifndef _PILERMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _PILERMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �Ǘ��N���X���`
//**********************************
class CPilerManager
{
public:
	CPilerManager();
	~CPilerManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(D3DXVECTOR3 *DestPos);

private:
	int m_nActiveTime;
	int m_nTimer;   // �o�ߎ��ԃJ�E���^
	int m_nCount;   // �o����
	enum STATE
	{
		STATE_IDLE,      // �T�[�N���҂�
		STATE_WAIT_PILER,// �~���҂�
		STATE_COOLTIME   // �N�[���^�C��
	};
	STATE m_State;

	D3DXVECTOR3 m_LastCirclePos;
};

#endif