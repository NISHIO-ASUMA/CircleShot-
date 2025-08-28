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
	// コンストラクタ・デストラクタ
	CBarrierDurability(int nPriority = static_cast<int>(CObject::PRIORITY::BARRIER));
	~CBarrierDurability();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* DestPos);

	// セッター
	void SetIdx(int nValue) { m_nIdx = nValue; }

	// 静的メンバ関数
	static CBarrierDurability* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,const char * pFilename);

private:
	int m_nIdx;		// 生成番号
};


#endif