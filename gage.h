//============================================
//
// ゲージ関係のクラス処理 [ gage.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _GAGE_H_ // このマクロ定義がされてなかったら
#define _GAGE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2D.h"

//**********************
// 前方宣言
//**********************
class CObject;

//**********************
// ゲージクラスを定義
//**********************
class CGage :public CObject2D
{
public:

	CGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue, float Height);

	static CGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	int m_nTextIdx;	// テクスチャ識別番号
};

#endif

