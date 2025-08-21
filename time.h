//====================================
//
// タイム処理 [ time.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TIME_H_ // このマクロ定義がされてなかったら
#define _TIME_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "number.h"
#include "object.h"

//**********************************
// タイムクラスを定義
//**********************************
class CTime : public CObject
{
public:
	CTime(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTime();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTime* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

	D3DXVECTOR3 GetPos(void) { return m_pos; }

	int GetAllTime(void) { return m_nAllTime; }
	void SetTexture(void);

private:
	static inline constexpr int DIGIT_TIME = 3;	// 桁数
	static inline constexpr int NUMTIME = 100;	// 最大タイマー
	static inline constexpr int CARVETIME = 60;	// カウント上限
	static inline constexpr int DIVIDE = 10;	// 桁分割の値

	D3DXVECTOR3 m_pos;		// 座標

	int m_nCurrentTime;		// 経過時間
	int m_nAllTime;			// 最大時間

	CNumber* m_pNumber[DIGIT_TIME];	// ナンバー型の静的変数

	float m_fHeight, m_fWidth;	// 横幅,高さ
	int m_nIdxTexture;			// テクスチャインデックス
};
#endif