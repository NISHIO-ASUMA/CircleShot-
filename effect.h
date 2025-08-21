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
// エフェクトクラスを定義 ( 継承 : ビルボード )
//*************************************************
class CEffect : public CBillboard
{
public:
	CEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffect();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetLife(int nLife) { m_nLife = nLife; }

	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);
	void SetTexture(void);

	int GetLife(void) { return m_nLife; }

private:
	int m_nLife;						  // 体力
	float m_fRadius;					  // 半径
	D3DXVECTOR3 m_move;					  // 移動量
	int m_nIdxTexture;					  // テクスチャインデックス
};

#endif
