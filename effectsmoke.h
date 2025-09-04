//==========================================
//
// 煙エフェクト処理 [ effectsmoke.h ]
// Author : Asuma Nishi
//
//==========================================

#ifndef _EFFECTSMOKE_H_	 // このマクロ定義がされてなかったら
#define _EFFECTSMOKE_H_	 // 2重インクルード防止のマクロ定義

//**********************************
// インクルードファイル
//**********************************
#include "billboard.h"

//**********************************
// 前方宣言
//**********************************
class CObject;

//**********************************
// 煙エフェクトクラスを定義
//**********************************
class CEffectSmoke : public CBillboard
{
public:
	CEffectSmoke(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectSmoke();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	static CEffectSmoke* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nIdxTex;		// テクスチャインデックス
	int m_nLife;		// 体力
	float m_fRadius;	// 半径
	D3DXVECTOR3 m_move;	// 移動量
};

#endif