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
	// �R���X�g���N�^�E�f�X�g���N�^
	CParameter();
	~CParameter();

	// �Z�b�^�[
	void SetHp(int nHp) { m_nHp = nHp; }
	void AddHp(int nValue) { m_nHp += nValue; }

	// �Q�b�^�[
	int GetHp()const { return m_nHp; }

private:
	int m_nHp; // �̗�
};

#endif
