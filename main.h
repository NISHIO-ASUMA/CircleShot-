//=====================================
//
// メイン関数 [ main.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MAIN_H_ // このマクロ定義がされてなかったら
#define _MAIN_H_ // 2重インクルード防止のマクロ定義

//*****************************
// メインプロセスクラスを定義
//*****************************
class CMainProc
{
public:
	// コンストラクタ・デストラクタ
	CMainProc();
	~CMainProc();

	// メンバ関数
	void ToggleFullScreen(HWND hWnd);

private:
	RECT m_Windowrect;	// ウィンドウの幅
};

#endif
