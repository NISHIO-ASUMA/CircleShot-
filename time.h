//====================================
//
// �^�C������ [ time.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TIME_H_ // ���̃}�N����`������ĂȂ�������
#define _TIME_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "number.h"
#include "object.h"

//**********************************
// �^�C���N���X���`
//**********************************
class CTime : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTime(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTime();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);

	// �Q�b�^�[
	int GetAllTime(void) { return m_nAllTime; }
	int GetcurrentTime(void) { return m_nCurrentTime; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	// �ÓI�����o�֐�
	static CTime* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	static inline constexpr int DIGIT_TIME = 3;	// ����
	static inline constexpr int NUMTIME = 100;	// �ő�^�C�}�[
	static inline constexpr int CARVETIME = 60;	// �J�E���g���
	static inline constexpr int DIVIDE = 10;	// �������̒l

	D3DXVECTOR3 m_pos;		// ���W

	int m_nCurrentTime;		// �o�ߎ���
	int m_nAllTime;			// �ő厞��

	CNumber* m_pNumber[DIGIT_TIME];	// �i���o�[�^�̐ÓI�ϐ�

	float m_fHeight, m_fWidth;	// ����,����
	int m_nIdxTexture;			// �e�N�X�`���C���f�b�N�X
};
#endif