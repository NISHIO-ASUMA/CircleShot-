//=========================================
//
// ゲーム管理処理 [ gamemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// インクルードファイル宣言
//***************************
#include "meshcylinder.h"
#include "boss.h"
#include "block.h"
#include "time.h"
#include "uimanager.h"

//*****************************
// ゲーム状態管理クラスを定義
//*****************************
class CGameManager
{
public:
	CGameManager();
	~CGameManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CBlock* GetBlock(void) { return m_pBlock; }
	static CMeshCylinder* GetCylinder(void) { return m_pMeshCylinder; }
	static CBoss* GetBoss(void) { return m_pBoss; }
	static CTime* GetTime(void) { return m_pTime; }
	static CUimanager* GetUimanager(void) {return m_puimanager;}

private:
	static CBlock* m_pBlock;					// ブロック
	static CMeshCylinder* m_pMeshCylinder;		// シリンダー
	static CBoss* m_pBoss;						// ボス
	static CTime* m_pTime;						// タイマー
	static CUimanager* m_puimanager;			// UIマネージャー

};

