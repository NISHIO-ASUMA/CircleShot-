//======================================
//
// UI全体を管理する処理 [ uimanager.h ]
// Author: Asuma Nishio
//
//======================================

#ifndef _UIMANAGER_H_ // このマクロ定義がされてなかったら
#define _UIMANAGER_H_ // 2重インクルード防止のマクロ定義

//****************************
// インクルードファイル宣言
//****************************
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "ui.h"

//****************************
// UI管理クラスを定義
//****************************
class CUimanager
{
public:
	CUimanager();
	~CUimanager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Load(const char* pFileName);
	void SetObjectUi(std::ifstream& file);

	
private:
	static int m_nIdxUi;				// UIのインデックス番号
	static std::vector<CUi*>m_aUidata;  // UI配列
};

#endif