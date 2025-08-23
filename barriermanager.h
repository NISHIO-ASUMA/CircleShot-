//===================================================
//
// バリアオブジェクトの管理処理 [ barriermanager.h ]
// Author : Asuma Nishio
//
//===================================================

#ifndef _BARRIERMANAGER_H_ // このマクロ定義がされてなかったら
#define _BARRIERMANAGER_H_ // 2重インクルード防止のマクロ定義

//************************************
// 前方宣言
//************************************
class CBarrierDurability;

//************************************
// バリアオブジェクト管理クラスを定義
//************************************
class CBarrierManager
{
public:
	CBarrierManager();
	~CBarrierManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void AddBarrier(int nValue);
	int GetNumBarrier() const { return m_nBarrierNum; }

private:
	int m_nBarrierNum; // バリア枚数
	CBarrierDurability* m_pBarrierUI; // UI描画用ポインタ

};

#endif