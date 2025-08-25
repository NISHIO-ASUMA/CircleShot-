//============================================
//
// シールド関数 [ barrierdurability.h ]
// Author : Asuma Nishio
// 
//============================================

#ifndef _BARRIERDURABILITY_H_ // このマクロ定義がされてなかったら
#define _BARRIERDURABILITY_H_ // 2重インクルード防止のマクロ定義

//*********************************
// インクルードファイル
//*********************************
#include "objectX.h"

//*********************************
// 前方宣言
//*********************************
class CObject;

//*********************************
// バリアオブジェクトクラスを定義
//*********************************
class CBarrierDurability : public CObjectX
{
public:
	CBarrierDurability(int nPriority = static_cast<int>(CObject::PRIORITY::BARRIER));
	~CBarrierDurability();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetIdx(int nValue) { m_nIdx = nValue; }

	bool Collision(D3DXVECTOR3* DestPos);

	static CBarrierDurability* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,const char * pFilename);

private:
	int m_nIdx;		// 生成番号
};


#endif