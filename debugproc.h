//========================================
//
// �f�o�b�O�v���Z�X���� [ debubgproc.h ]
// Author: Asuma Nishio
//
//========================================

#ifndef _DEBUGPROC_H_  // ���̃}�N����`������ĂȂ�������
#define _DEBUGPROC_H_  // 2�d�C���N���[�h�h�~�̃}�N����`

//*************************
// �f�o�b�O�N���X���`
//*************************
class CDebugproc
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CDebugproc();
	~CDebugproc();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �ÓI�����o�֐�
	static void Draw(int PosX, int PosY);
	static void Print(const char* fmt, ...);

private:
	static LPD3DXFONT m_pFont; // �f�o�b�O�t�H���g
	static char m_aStr[MAX_WORD];		// ������i�[�o�b�t�@
	static bool m_isUse;
};

#endif