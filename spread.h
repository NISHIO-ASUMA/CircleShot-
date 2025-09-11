//=====================================
//
// 拡散オブジェクト処理 [ spread.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SPREAD_H_ // このマクロ定義がされてなかったら
#define _SPREAD_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "objectX.h"

//*****************************
// 拡散オブジェクト処理
//*****************************
class CSpread : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CSpread(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CSpread();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CSpread* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	float m_fUpSpeed;	// 上昇速度
	int m_nBounceCount;	// 回数
};

#endif