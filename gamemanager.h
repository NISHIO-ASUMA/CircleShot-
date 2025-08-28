//==========================================
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
#include "barriermanager.h"
#include "rubblemanager.h"

//*****************************
// 前方宣言
//*****************************
class CItemManager;

//*****************************
// ゲーム状態管理クラスを定義
//*****************************
class CGameManager
{
public:
	// コンストラクタ・デストラクタ
	CGameManager();
	~CGameManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// 静的メンバ関数
	static CMeshCylinder* GetCylinder(void) { return m_pMeshCylinder; }
	static CBoss* GetBoss(void) { return m_pBoss; }
	static CTime* GetTime(void) { return m_pTime; }
	static CUimanager* GetUimanager(void) { return m_puimanager; }
	static CBarrierManager* GetBarrier(void) { return m_pBarrier; }
	static CRubbleManager* GetRubble(void) { return m_pRubble; }

private:
	static CMeshCylinder* m_pMeshCylinder;		// シリンダー
	static CBoss* m_pBoss;						// ボス
	static CTime* m_pTime;						// タイマー
	static CUimanager* m_puimanager;			// UIマネージャー
	static CBarrierManager* m_pBarrier;
	static CRubbleManager* m_pRubble;

	CItemManager* m_pItemManager;		// アイテムマネージャーポインタ

};

