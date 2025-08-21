//====================================
//
// 攻撃前兆演出 [ attacksign.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _ATTACKSIGN_H_ // このマクロ定義がされてなかったら
#define _ATTACKSIGN_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2d.h"

//**********************
// 前方宣言
//**********************
class CObject;

//**********************
// 攻撃前兆クラスを定義
//**********************
class CAttackSign : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CAttackSign(int nPriority = static_cast<int>(CObject::PRIORITY::BILLBOARD));
	~CAttackSign();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(void);

	// 静的メンバ関数
	static CAttackSign* Create(float fWidth, float fHeight);

private:
	int m_nidxTex;		// テクスチャインデックス
	int m_nLife;		// 寿命
};

#endif

