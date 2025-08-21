//==============================================
//
// リザルトシーン管理処理 [ resultmanager.h ]
// Author: Asuma Nishio
// 
//==============================================

#ifndef _RESULTMANAGER_H_ // このマクロ定義がされてなかったら
#define _RESULTMANAGER_H_ // 2重インクルード防止のマクロ定義

//**************************
// リザルト管理クラスを定義
//**************************
class CResultManager
{
public:
	CResultManager();
	~CResultManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	bool m_isKeyDown;
};

#endif

