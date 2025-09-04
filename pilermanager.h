//===============================================
//
// 円柱攻撃管理処理 [ pilermanager.h ]
// Author : Asuma Nishio
//
//===============================================

#ifndef _PILERMANAGER_H_ // このマクロ定義がされてなかったら
#define _PILERMANAGER_H_ // 2重インクルード防止のマクロ定義

//**********************************
// 管理クラスを定義
//**********************************
class CPilerManager
{
public:
	CPilerManager();
	~CPilerManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(D3DXVECTOR3 *DestPos);

private:
	int m_nActiveTime;
	int m_nTimer;   // 経過時間カウンタ
	int m_nCount;   // 出現回数
	enum STATE
	{
		STATE_IDLE,      // サークル待ち
		STATE_WAIT_PILER,// 円柱待ち
		STATE_COOLTIME   // クールタイム
	};
	STATE m_State;

	D3DXVECTOR3 m_LastCirclePos;
};

#endif