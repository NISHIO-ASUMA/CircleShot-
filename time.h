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
	// コンストラクタ・デストラクタ
	CTime(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTime();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Save(void);

	// セッター
	void SetTexture(void);

	// ゲッター
	int GetAllTime(void) { return m_nAllTime; }
	int GetcurrentTime(void) { return m_nCurrentTime; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	// 静的メンバ関数
	static CTime* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	static inline constexpr int DIGIT_TIME = 3;	// 桁数
	static inline constexpr int NUMTIME = 120;	// 最大タイマー
	static inline constexpr int CARVETIME = 60;	// カウント上限
	static inline constexpr int DIVIDE = 10;	// 桁分割の値

	int m_nCurrentTime;		// 現在時間
	int m_nAllTime;			// 最大時間
	int m_nDecTime;			// 減った時間量
	int m_nIdxTexture;			// テクスチャインデックス
	float m_fHeight, m_fWidth;	// 横幅,高さ

	CNumber* m_pNumber[DIGIT_TIME];	// ナンバー型の静的変数
	D3DXVECTOR3 m_pos;		// 座標
};
#endif