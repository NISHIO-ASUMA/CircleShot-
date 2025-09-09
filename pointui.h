//=====================================
//
// 選択ポイントUI処理 [ pointui.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _POINTUI_H_ // このマクロ定義がされてなかったら
#define _POINTUI_H_ // 2重インクルード防止のマクロ定義

//*****************************
// インクルードファイル
//*****************************
#include "object2D.h"

//*********************************
// 選択ポイント表示UIクラスを定義
//*********************************
class CPointUi : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CPointUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CPointUi();
	
	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	// 静的メンバ関数
	static CPointUi* Create(D3DXVECTOR3 pos);

private:
	int m_nIdxTex;	// テクスチャインデックス

};

#endif