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
	CMapManager(int nPriority = static_cast<int>(CObject::PRIORITY::BLOCK));
	~CMapManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CMapObject* GetInfo(const int nIdx) { return m_MapObj[nIdx]; }

	void PushBack(CMapObject* pMapOjbect) { m_MapObj.push_back(pMapOjbect); };
	static CMapManager* Craete(void);

private:
	std::vector<CMapObject*>m_MapObj;
	int m_nSelectIdx;

};

#endif
