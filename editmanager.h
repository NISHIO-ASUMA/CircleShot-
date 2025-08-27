//============================================
//
// エディターシーン管理処理 [ editmanager.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _EDITMANAGER_H_ // このマクロ定義がされてなかったら
#define _EDITMANAGER_H_ // 2重インクルード防止のマクロ定義

class CRubble;
class CMapManager;

#include "modellist.h"

//**********************************
// エディター管理クラスを定義
//**********************************
class CEditManager
{
public:
	CEditManager();
	~CEditManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);

private:

	static constexpr int MAX_EDITOBJ = 256;

	int m_nSelectIndex; // 選択中オブジェクトのインデックス
	float m_moveSpeed;
	float m_rotSpeed;

	CRubble* m_pRubbleObj[MAX_EDITOBJ]; 	// Rubbleのオブジェクトポインタ
	CMapManager* m_pMapManager;
};

#endif
