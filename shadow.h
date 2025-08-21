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
	CShadow(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadow();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	void SetTexture(void);
	void UpdatePos(D3DXVECTOR3 pos);

private:
	int m_nTexIdx;  // テクスチャインデックス番号
};

#endif
