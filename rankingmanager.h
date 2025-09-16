//==========================================
//
// ランキング管理処理 [ rankingmanager.h ]
// Author: Asuma Nishio
//
//==========================================

#ifndef _RANKINGMANAGER_H_ // このマクロ定義がされてなかったら
#define _RANKINGMANAGER_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル宣言
//******************************
class CRankingManager
{
public:
	CRankingManager();
	~CRankingManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

};

#endif