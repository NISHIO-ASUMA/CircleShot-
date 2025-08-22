//===================================
//
// アイテム処理 [ item.h ]
// Author: Asuma Nishio
//
//===================================

#ifndef _ITEM_H_ // このマクロ定義がされてなかったら
#define _ITEM_H_ // 2重インクルード防止のマクロ定義

//**************************
// インクルードファイル宣言
//**************************
#include "objectX.h"

//****************************
// 前方宣言
//****************************
class CObject;

//****************************
// アイテムクラスを定義
//****************************
class CItem : public CObjectX
{
public:
	CItem(int nPriority = static_cast<int>(CObject::PRIORITY::ITEM));
	~CItem();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char* Filename);

	bool Collision(D3DXVECTOR3* pPos);

private:
};

#endif