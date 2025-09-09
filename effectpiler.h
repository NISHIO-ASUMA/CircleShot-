//======================================
//
// 柱状エフェクト処理 [ effectpiler.h ]
// Author: Asuma Nishio
//
//======================================

#ifndef _EFFECTPILER_H_ // このマクロ定義がされてなかったら
#define _EFFECTPILER_H_ // 2重インクルード防止のマクロ定義

//**************************  
// インクルードファイル宣言
//**************************
#include "billboard.h"

//**************************  
// エフェクトクラスを定義
//**************************
class CEffectPiler : public CBillboard
{
public:
	// コンストラクタ・デストラクタ
	CEffectPiler(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectPiler();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	// 静的メンバ関数
	static CEffectPiler* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife);

private:
	int m_nLife;		// 体力
	float m_fRadius;	// 半径
	int m_nIdxTex;
};

#endif
