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
	CResultManager();
	~CResultManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	bool m_isKeyDown;
};

#endif

