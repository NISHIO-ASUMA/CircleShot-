//====================================
//
// ���C���֐� [ main.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MAIN_H_ // ���̃}�N����`������ĂȂ�������
#define _MAIN_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//****************************
// �}�N����`
//****************************
#define CLASS_NAME "WindowClass"		// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME "Circle Shot!"		// �E�C���h�E�̖��O

//*****************************
// ���C���v���Z�X�N���X���`
//*****************************
class CMainProc
{
public:
	CMainProc();
	~CMainProc();

	void ToggleFullScreen(HWND hWnd);

private:
	RECT m_Windowrect;	// �E�B���h�E�̕�
};

#endif
