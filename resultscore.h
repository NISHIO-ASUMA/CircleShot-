//=======================================
//
// リザルトスコア処理 [ resultscore.h ]
// Author: Asuma Nishio
// 
//=======================================

#ifndef _RESULTSCORE_H_ // このマクロ定義がされてなかったら
#define _RESULTSCORE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "number.h"
#include "object.h"

//****************************
// リザルトスコアクラスを定義
//****************************
class CResultScore : public CObject
{
public:
	//****************************
	// 種類定義
	//****************************
	enum TYPE
	{
		SCORE_GAME,
		SCORE_TIME,
		SCORE_LAST,
		SCORE_MAX
	};

	// コンストラクタ・デストラクタ
	CResultScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultScore();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(void);
	void SetScore(int nResultValue) { m_nScore = nResultValue; }
	void SetTimeScore(int nResultValue) { m_nTimeScore = nResultValue; }
	void SetLastScore(int nResultValue, int nResultValue1) { m_nLastScore = nResultValue + nResultValue1; }

	int MathTimescore(void);

	// 静的メンバ関数
	static CResultScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType);

private:
	static constexpr int NUM_RESULTSCORE = 8; // 桁数
	static constexpr int NUM_RESULTDIGIT = 10; // 表示する分割桁数の値

	int m_nScore;			// スコア保持用
	int m_nTimeScore;		// 時間のスコア
	int m_nLastScore;		// 最終保存スコア
	int m_nType;			// 種類

	CNumber* m_apNumber[NUM_RESULTSCORE];	// 桁数分のナンバーのポインタ
	D3DXVECTOR3 m_pos;		// 座標
	float m_fWidth;			// 横幅
	float m_fHeight;		// 高さ
	int m_nIdxTexture;		// テクスチャインデックス
};

#endif