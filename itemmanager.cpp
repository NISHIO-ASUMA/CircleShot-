//============================================
//
// アイテム管理処理 [ itemmanager.cpp ]
// Author : Asuma Nishio
// 
// TODO : アイテムの生成,管理をする
//
//============================================

//*********************************
// インクルードファイル
//*********************************
#include "itemmanager.h"
#include "gamemanager.h"
#include "time.h"
#include "item.h"

//=================================
// コンストラクタ
//=================================
CItemManager::CItemManager()
{
	// 値のクリア
}
//=================================
// デストラクタ
//=================================
CItemManager::~CItemManager()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CItemManager::Init(void)
{
	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CItemManager::Uninit(void)
{
	// 各種終了処理

}
//=================================
// 更新処理
//=================================
void CItemManager::Update(void)
{
	// タイマーを取得
	CTime* pTime = CGameManager::GetTime();

	if (pTime == nullptr) return;

	// タイマーを取得
	int NowTime = pTime->GetAllTime();

	static int lastSpawnTime = -1;

	// 5秒ごとに生成
	if (NowTime % 5 == 0 && NowTime != lastSpawnTime)
	{
		// ランダム生成
		int nActivePos = rand() % 3;

		// アイテム生成
		CItem::Create(m_ActivePointPos[nActivePos], VECTOR3_NULL, "data\\MODEL\\STAGEOBJ\\Guard000.x");

		lastSpawnTime = NowTime;
	}
}
