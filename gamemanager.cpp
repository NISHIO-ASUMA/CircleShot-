//==========================================
//
// ゲーム管理処理 [ gamemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// インクルードファイル宣言
//***************************
#include "gamemanager.h"
#include "manager.h"
#include "debugproc.h"
#include "score.h"
#include "time.h"
#include "meshdome.h"
#include "meshfield.h"
#include "player.h"
#include "meshimpact.h"
#include "playerlifegage.h"
#include "bosslifegage.h"
#include "parameter.h"
#include "result.h"
#include "sound.h"
#include "item.h"
#include "barrierdurability.h"
#include "bullethorming.h"
#include "itemmanager.h"
#include "charge.h"
#include "sceneloader.h"
#include "ui.h"
#include "texture.h"
#include "pilermanager.h"
#include "spread.h"
#include "bulleticon.h"
#include "result.h"

//**************************
// 静的メンバ変数宣言
//**************************
CMeshCylinder* CGameManager::m_pMeshCylinder = nullptr;	// 円柱
CBoss* CGameManager::m_pBoss = nullptr;					// ボス
CTime* CGameManager::m_pTime = nullptr;					// タイマー
CUimanager* CGameManager::m_puimanager = nullptr;		// UIマネージャー
CBarrierManager* CGameManager::m_pBarrier = nullptr;	// バリアマネージャー
CRubbleManager* CGameManager::m_pRubble = nullptr;		// 瓦礫オブジェクトマネージャー

//========================
// コンストラクタ
//========================
CGameManager::CGameManager()
{
	// 値のクリア
}
//========================
// デストラクタ
//========================
CGameManager::~CGameManager()
{
	// 無し
}
//========================
// 初期化処理
//========================
HRESULT CGameManager::Init(void)
{
	// シリンダー生成
	m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 550.0f);

	// ボス生成
	m_pBoss = CBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f), 60.0f, 500);

	// シーンオブジェクト読み込み
	CSceneLoader::SplitLoad(2);

	// タイマー生成
	m_pTime = CTime::Create(D3DXVECTOR3(1220.0f, 670.0f, 0.0f), 80.0f, 50.0f);

	// フレーム作成
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 65.0f, 0.0f), 0, 65.0f, 65.0f, "data\\TEXTURE\\alert_frame.png", false);
	CUi::Create(D3DXVECTOR3(180.0f, 670.0f, 0.0f), 0, 170.0f, 40.0f, "data\\TEXTURE\\Pause_ui.png", false);

	// あとで修正 CBulletIconクラスでインデックスに応じて選択されているとき色を白,されてないとき透明に変更する処理を書く
	// CUi::Create(D3DXVECTOR3(180.0f, 180.0f, 0.0f), 0, 30.0f, 30.0f, "data\\TEXTURE\\Laser_Icon.png", false);

	CBulletIcon::Create(D3DXVECTOR3(90.0f, 180.0f, 0.0f), "data\\TEXTURE\\Laser_Icon.png", 0);
	CBulletIcon::Create(D3DXVECTOR3(180.0f, 180.0f, 0.0f), "data\\TEXTURE\\Laser_Icon.png", 1);

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// nullだったら
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);

	// バリアマネージャー生成
	 m_pBarrier = new CBarrierManager;

	// nullじゃなかったら初期化
	if (m_pBarrier != nullptr)
	{
		// 初期化処理
		m_pBarrier->Init();
	}

	//// uiマネージャー生成
	//m_puimanager = new CUimanager;

	//// nullじゃなかったら初期化
	//if (m_puimanager != nullptr)
	//{
	//	// 初期化処理
	//	m_puimanager->Init();
	//}

	// 瓦礫オブジェクトマネージャー生成
	m_pRubble = new CRubbleManager;

	// nullじゃなかったら初期化
	if (m_pRubble != nullptr)
	{
		// 初期化処理
		m_pRubble->Init();
	}

	// アイテムマネージャー生成
	m_pItemManager = new CItemManager;

	// nullじゃなかったら
	if (m_pItemManager != nullptr)
	{
		// 初期化処理
		m_pItemManager->Init();
	}

	m_pPilerManager = new CPilerManager;

	// nullじゃなかったら
	if (m_pPilerManager != nullptr)
	{
		// 初期化処理
		m_pPilerManager->Init();
	}

	// 初期化結果を返す
	return S_OK;
}
//========================
// 終了処理
//========================
void CGameManager::Uninit(void)
{
	// 使用したポインタのnull初期化
	m_pBoss = nullptr;
	m_pMeshCylinder = nullptr;
	m_pTime = nullptr;

	//// nullじゃなかったら
	//if (m_puimanager != nullptr)
	//{
	//	// 終了処理
	//	m_puimanager->Uninit();

	//	// ポインタの破棄
	//	delete m_puimanager;

	//	// null初期化
	//	m_puimanager = nullptr;
	//}

	// nullじゃなかったら
	if (m_pBarrier != nullptr)
	{
		// 終了処理
		m_pBarrier->Uninit();

		// ポインタの破棄
		delete m_pBarrier;

		// null初期化
		m_pBarrier = nullptr;
	}

	// nullじゃなかったら
	if (m_pRubble != nullptr)
	{
		// 終了処理
		m_pRubble->Uninit();

		// ポインタの破棄
		delete m_pRubble;

		// null初期化
		m_pRubble = nullptr;
	}

	// nullじゃなかったら
	if (m_pItemManager != nullptr)
	{
		// 終了処理
		m_pItemManager->Uninit();

		// ポインタの破棄
		delete m_pItemManager;

		// null初期化
		m_pItemManager = nullptr;
	}

	// nullじゃなかったら
	if (m_pPilerManager != nullptr)
	{
		// 終了処理
		m_pPilerManager->Uninit();

		// ポインタの破棄
		delete m_pPilerManager;

		// null初期化
		m_pPilerManager = nullptr;
	}
}
//========================
// 更新処理
//========================
void CGameManager::Update(void)
{
	// プレイヤー取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (pPlayer == nullptr) return;

	// 過去の座標取得
	D3DXVECTOR3 pos = pPlayer->GetOldPos();

	// nullじゃなかったら
	if (m_pBarrier != nullptr)
	{
		// 更新処理
		m_pBarrier->Update();
	}

	// nullじゃなかったら
	if (m_pItemManager != nullptr)
	{
		// 更新処理
		m_pItemManager->Update();
	}

	// nullじゃなかったら
	if (m_pPilerManager != nullptr)
	{
		// 更新処理
		m_pPilerManager->Update(&pos);
	}

#ifdef _DEBUG

	// 検証用オブジェクト出現
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_O))
	{
		// 減算回数を加算
		CScore::DecScore();
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_L))
	{
		CManager::GetFade()->SetFade(new CResult());

		return;

		// ファイル処理
		// m_pRubble->LoadSplitFile(m_pRubble->FILETYPE_SMALL);
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_N))
	{
		// スコアを保存
		CScore::SaveScore();
	}
#endif
}