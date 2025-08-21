//====================================
//
// スコア処理 [ score.h ]
// Author: Asuma Nishio
//
// TODO : 2Dは手前に描画するので番号は7
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
// スコアクラスを定義 ( オブジェクト継承 )
//*******************************************
class CScore : public CObject
{
public:
	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static void AddScore(int nValue);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetTexture(void);

	static inline constexpr int NUM_SCORE = 8; // 桁数

private: 
	
	static int m_nScore;			// スコア保持用

	CNumber *m_apNumber[NUM_SCORE];	// 桁数分のナンバーのポインタ
	D3DXCOLOR m_col;				// カラー
	D3DXVECTOR3 m_pos;				// 座標
	D3DXVECTOR3 m_rot;				// 角度]
	

	float m_fWidth;					// 横幅
	float m_fHeight;				// 高さ
	int m_nIdxTexture;				// テクスチャインデックス


};
#endif