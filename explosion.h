//====================================
//
// 爆発処理 [ explosion.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _EXPLOSION_H_ // このマクロ定義がされてなかったら
#define _EXPLOSION_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2D.h"

//**************************
// 爆発クラスを定義
//**************************
class CExplosion : public CObject2D
{
public:

	// コンストラクタ・デストラクタ
	CExplosion(int nPriority = 3);
	~CExplosion();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture();

	// 静的メンバ関数
	static CExplosion* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,D3DXCOLOR col);


private:
	int m_nIdxTexture;	// テクスチャインデックス
};

#endif