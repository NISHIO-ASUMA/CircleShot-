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

	// 座標リスト
	D3DXVECTOR3 m_ActivePointPos[3] =
	{
		{100.0f,50.0f,-550.0f},
		{100.0f,50.0f,550.0f},
		{0.0f,0.0f,0.0f},
	};
};

#endif
