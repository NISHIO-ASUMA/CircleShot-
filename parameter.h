//====================================
//
// �p�����[�^���� [ parameter.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PARAMETER_H_ // ���̃}�N����`������ĂȂ�������
#define _PARAMETER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �p�����[�^�[�N���X���`
//******************************
class CParameter
{
public:
	CParameter();
	~CParameter();

	int GetHp()const { return m_nHp; }

	void SetHp(int nHp) { m_nHp = nHp; }
	void AddHp(int nValue) { m_nHp += nValue; }
	
private:
	int m_nHp; // �̗�
};

#endif
