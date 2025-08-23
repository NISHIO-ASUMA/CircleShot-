//============================================
//
// アイテム管理処理 [ itemmanager.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _ITEMMANAGER_H_ // このマクロ定義がされてなかったら
#define _ITEMMANAGER_H_ // 2重インクルード防止のマクロ定義

//*********************************
// アイテム全体の管理クラスを定義
//*********************************
class CItemManager
{
public:
	CItemManager();
	~CItemManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};

#endif
