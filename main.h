//====================================
//
// メイン関数 [ main.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MAIN_H_ // このマクロ定義がされてなかったら
#define _MAIN_H_ // 2重インクルード防止のマクロ定義

//****************************
// マクロ定義
//****************************
#define CLASS_NAME "WindowClass"		// ウインドウクラスの名前
#define WINDOW_NAME "Circle Shot!"		// ウインドウの名前

//*****************************
// メインプロセスクラスを定義
//*****************************
class CMainProc
{
public:
	CMainProc();
	~CMainProc();

	void ToggleFullScreen(HWND hWnd);

private:
	RECT m_Windowrect;	// ウィンドウの幅
};

#endif
