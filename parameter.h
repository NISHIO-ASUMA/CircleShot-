//====================================
//
// パラメータ処理 [ parameter.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PARAMETER_H_ // このマクロ定義がされてなかったら
#define _PARAMETER_H_ // 2重インクルード防止のマクロ定義

//******************************
// パラメータークラスを定義
//******************************
class CParameter
{
public:
	// コンストラクタ・デストラクタ
	CParameter();
	~CParameter();

	// セッター
	void SetHp(int nHp) { m_nHp = nHp; }
	void AddHp(int nValue) { m_nHp += nValue; }

	// ゲッター
	int GetHp()const { return m_nHp; }

private:
	int m_nHp; // 体力
};

#endif
