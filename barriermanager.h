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
	// コンストラクタ・デストラクタ
	CBarrierManager();
	~CBarrierManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void DamageBarrier(int nValue);

	// セッター
	void AddBarrier(int nValue, D3DXVECTOR3 playerPos, float fRadius);

	// ゲッター
	int GetNumBarrier() const { return m_nBarrierNum; }

private:

	static inline constexpr int MAX_GUARD = 3; // 最大バリア数

	int m_nBarrierNum; // バリア枚数
	CBarrierDurability* m_pBarrierObj[MAX_GUARD]; // バリアオブジェクトのポインタ

};

#endif