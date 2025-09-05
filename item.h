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
	//****************************
	// アイテムの種類
	//****************************
	enum TYPE
	{
		TYPE_GUARD,	// ガード
		TYPE_LIFE,	// 体力回復
		TYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CItem(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CItem();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* pPos);

	// 静的メンバ関数
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);

private:
	int m_nType;	// アイテムの種類
};

#endif