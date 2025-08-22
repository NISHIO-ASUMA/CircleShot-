//============================================
//
// シールド耐久値関数 [ barrierdurability.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _BARRIERDURABILITY_H_ // このマクロ定義がされてなかったら
#define _BARRIERDURABILITY_H_ // 2重インクルード防止のマクロ定義

//*********************************
// インクルードファイル
//*********************************
#include "object2D.h"

//*********************************
// 前方宣言
//*********************************
class CObject;

//*********************************
// 耐久値クラスを定義
//*********************************
class CBarrierDurability : public CObject2D
{
public:
	CBarrierDurability(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBarrierDurability();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetTexture(int nType);
	void SetCreateFlag(bool isFlags) { m_isCreate = isFlags;}

	static CBarrierDurability* Create(D3DXVECTOR3 pos, float fHeight, float fWidth, int nType);

private:
	int m_nIdxTex; // テクスチャインデックス
	bool m_isCreate; // 生成可能かどうか
};


#endif