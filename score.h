//====================================
//
// スコア処理 [ score.h ]
// Author: Asuma Nishio
// 
//=====================================

#ifndef _SCORE_H_ // このマクロ定義がされてなかったら
#define _SCORE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "number.h"
#include "object.h"

//*******************************************
// スコアクラスを定義
//*******************************************
class CScore : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(void);

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	// 静的メンバ関数
	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static void AddScore(int nValue);
	static void DecScore(void);
	static int GetScore(void) { return m_nScore; }
	static void SaveScore(void);
	static void SetScore(int nDestScore) { m_nScore = nDestScore; }

private: 
	static constexpr int NUM_SCORE = 8; // 桁数
	static constexpr int NUM_DIGIT = 10; // 表示する分割桁数の値

	static int m_nScore;			// スコア保持用
	static int m_nDecCount;			// 減算した回数

	CNumber *m_apNumber[NUM_SCORE];	// 桁数分のナンバーのポインタ
	D3DXCOLOR m_col;				// カラー
	D3DXVECTOR3 m_pos;				// 座標
	D3DXVECTOR3 m_rot;				// 角度
	
	float m_fWidth;					// 横幅
	float m_fHeight;				// 高さ
	int m_nIdxTexture;				// テクスチャインデックス
};
#endif