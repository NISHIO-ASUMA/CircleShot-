//========================================
//
// マップマネージャー処理 [ mapmanager.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _MAPMANAGER_H_ // このマクロ定義がされてなかったら
#define _MAPMANAGER_H_ // 2重インクルード防止のマクロ定義

//***************************
// インクルードファイル
//***************************
#include "object.h"
#include <vector>

//***************************
// 前方宣言
//***************************
class CMapObject;

//***************************
// マップマネージャークラス
//***************************
class CMapManager : CObject
{
public:
	// コンストラクタ・デストラクタ
	CMapManager(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CMapManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PushBack(CMapObject* pMapOjbect) { m_MapObj.push_back(pMapOjbect); };

	// ゲッター
	CMapObject* GetInfo(const int nIdx) { return m_MapObj[nIdx]; }
	int GetSize() const { return (int)m_MapObj.size(); }

	// 静的メンバ関数
	static CMapManager* Craete(void);

private:
	std::vector<CMapObject*>m_MapObj;

};

#endif
