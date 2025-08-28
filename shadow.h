//====================================
//
// 影処理 [ shadow.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SHADOW_H_ // このマクロ定義がされてなかったら
#define _SHADOW_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object3D.h"

//*****************************
// 影クラスを定義
//*****************************
class CShadow : public CObject3D
{
public:
	// コンストラクタ・デストラクタ
	CShadow(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadow();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UpdatePos(D3DXVECTOR3 pos);

	// 静的メンバ関数
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	// セッター
	void SetTexture(void);

private:
	int m_nTexIdx;  // テクスチャインデックス番号
};

#endif
