//==============================================
//
// ���U���g�V�[���Ǘ����� [ resultmanager.h ]
// Author: Asuma Nishio
// 
//==============================================

#ifndef _RESULTMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _RESULTMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// ���U���g�Ǘ��N���X���`
//**************************
class CResultManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CResultManager();
	~CResultManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	bool m_isKeyDown; // �L�[���̓t���O
};

#endif

