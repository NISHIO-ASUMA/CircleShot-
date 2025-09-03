//=========================================
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
#include "effectlaser.h"
#include "charge.h"
#include "sceneloader.h"
#include <fstream>
#include <iostream>
#include <sstream>

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
	CSceneLoader::SplitLoad(1);

	// タイマー生成
	m_pTime = CTime::Create(D3DXVECTOR3(1220.0f, 670.0f, 0.0f), 80.0f, 50.0f);

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

	// uiマネージャー生成
	m_puimanager = new CUimanager;

	// nullじゃなかったら初期化
	if (m_puimanager != nullptr)
	{
		// 初期化処理
		m_puimanager->Init();
	}

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

	// nullじゃなかったら
	if (m_puimanager != nullptr)
	{
		// 終了処理
		m_puimanager->Uninit();

		// ポインタの破棄
		delete m_puimanager;

		// null初期化
		m_puimanager = nullptr;
	}

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
}
//========================
// 更新処理
//========================
void CGameManager::Update(void)
{
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
#ifdef _DEBUG

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_O))
	{
		CBulletHorming::Create("data\\MODEL\\ATTACKMODEL\\bulletobject000.x", D3DXVECTOR3(0.0f, 300.0f, 0.0f));
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_L))
	{
		// ファイル処理
		m_pRubble->LoadSplitFile(m_pRubble->FILETYPE_SMALL);
	}
#endif
}
#if 0

//// プレイヤー生成
//// ドーム生成
//CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

//// ドーム生成
//CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);

//// フィールド生成
//CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

//CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 0, "data\\MOTION\\Player\\Player100motion.txt");
//CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 1, "data\\MOTION\\Player\\Player200motion.txt");

////地面ブロック配置
//CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

//// プレイヤー体力ゲージ生成
//CPlayerLifeGage::Create(D3DXVECTOR3(95.0f, 38.0f, 0.0f), 0.0f, 0.0f, CPlayerLifeGage::GAGE_BAR);
//CPlayerLifeGage::Create(D3DXVECTOR3(3.0f, 0.0f, 0.0f), 450.0f, 100.0f, CPlayerLifeGage::GAGE_FRAME);

//// ボス体力ゲージ生成
//CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), 0.0f, 0.0f, CBossLifeGage::TYPE_GAGE);
//CBossLifeGage::Create(D3DXVECTOR3(770.0f, 0.0f, 0.0f), SCREEN_WIDTH * 0.4f, 60.0f, CBossLifeGage::TYPE_FRAME);

//// レーザーゲージ生成
//CCharge::Create(D3DXVECTOR3(138.0f, 98.0f, 0.0f), 0.0f, 0.0f, CCharge::CHARGE_BAR);
//CCharge::Create(D3DXVECTOR3(0.0f, 95.0f, 0.0f), 450.0f, 45.0f, CCharge::CHARGE_FRAME);

#endif