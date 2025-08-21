//====================================
//
// ポーズ管理処理 [ pausemanager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PAUSEMANAGER_H_ // このマクロ定義がされてなかったら
#define _PAUSEMANAGER_H_ // 2重インクルード防止のマクロ定義

//********************************
// インクルードファイル宣言
//********************************
#include "pause.h"

//*********************************
// ポーズメニュー管理クラスを定義
//*********************************
class CPauseManager
{
public:
	CPauseManager();
	~CPauseManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetEnablePause(bool isFlags) { m_isPause = isFlags; }
	void SetEnablePause(void);

	static bool GetPause(void) { return m_isPause; }

private:
	static constexpr int SELECT_MAX = 4; // 最大メニュー選択数
	static constexpr float SPACEHEIGHT = 160.0f; // ポリゴン同士の間隔

	int m_nSelectIdx;	// セレクト番号
	static bool m_isPause;		// ポーズかどうか
	CPause* m_pPause[SELECT_MAX]; // ポーズクラスのポインタ配列
	
};

#endif
