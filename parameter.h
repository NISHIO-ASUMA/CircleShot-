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
	CParameter();
	~CParameter();

	int GetHp()const { return m_nHp; }

	void SetHp(int nHp) { m_nHp = nHp; }
	void AddHp(int nValue) { m_nHp += nValue; }
	
private:
	int m_nHp; // 体力
};

#endif
