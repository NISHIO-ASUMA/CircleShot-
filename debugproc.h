//========================================
//
// デバッグプロセス処理 [ debubgproc.h ]
// Author: Asuma Nishio
//
//========================================

#ifndef _DEBUGPROC_H_  // このマクロ定義がされてなかったら
#define _DEBUGPROC_H_  // 2重インクルード防止のマクロ定義

//*************************
// デバッグクラスを定義
//*************************
class CDebugproc
{
public:
	CDebugproc();
	~CDebugproc();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static void Draw(int PosX, int PosY);
	static void Print(const char* fmt, ...);

private:
	
	static LPD3DXFONT m_pFont; // デバッグフォント
	static char m_aStr[MAX_WORD];		// 文字列格納バッファ
	static bool m_isUse;
};

#endif