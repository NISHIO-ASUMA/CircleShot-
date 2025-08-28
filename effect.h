//====================================
//
// エフェクト処理 [ effect.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _EFFECT_H_ // このマクロ定義がされてなかったら
#define _EFFECT_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "billboard.h"

//*************************************************
// エフェクトクラスを定義
//*************************************************
class CEffect : public CBillboard
{
public:
	// コンストラクタ・デストラクタ
	CEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffect();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetLife(int nLife) { m_nLife = nLife; }
	void SetTexture(void);

	// ゲッター
	int GetLife(void) { return m_nLife; }

	// 静的メンバ関数
	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;						  // 体力
	float m_fRadius;					  // 半径
	D3DXVECTOR3 m_move;					  // 移動量
	int m_nIdxTexture;					  // テクスチャインデックス
};

#endif
