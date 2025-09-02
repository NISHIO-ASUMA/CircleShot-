//=========================================================
//
// UIエディターオブジェクト管理処理 [ uiobjectmanager.h ]
// Author : Asuma Nishio
// 
// TODO : 家で作業する
//
//=========================================================

#ifndef _UIOBJECTMANAGER_H_ // このマクロ定義がされてなかったら
#define _UIOBJECTMANAGER_H_ // 2重インクルード防止のマクロ定義

//**********************************
// インクルードファイル
//**********************************
#include "object.h"
#include <vector>

//***************************
// 前方宣言
//***************************
class CUiObject;

//**********************************
// 管理クラスを定義
//**********************************
class CUiObjectManager : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CUiObjectManager(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUiObjectManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PushBack(CUiObject* pMapOjbect) { m_UiObj.push_back(pMapOjbect); };

	// ゲッター
	CUiObject* GetInfo(const int nIdx) { return m_UiObj[nIdx]; }
	int GetSize() const { return (int)m_UiObj.size(); }

	// 静的メンバ関数
	static CUiObjectManager* Craete(void);

private:
	std::vector<CUiObject*>m_UiObj;	// 動的リスト
};

#endif