//=================================================
//
// チュートリアル管理処理 [ tutorialmanager.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// インクルードファイル
//**********************
#include "tutorialmanager.h"
#include "tutorialui.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "sceneloader.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "meshfield.h"
#include "player.h"
#include "tutotask.h"
#include "tutorialboss.h"

//==========================
// コンストラクタ
//==========================
CTutorialManager::CTutorialManager()
{
	// 値のクリア
	m_pTutoui = nullptr;
	m_pTask = nullptr;
	m_Tasktype = TASKTYPE_MOVE;
}
//==========================
// デストラクタ
//==========================
CTutorialManager::~CTutorialManager()
{
	// 無し
}
//==========================
// 初期化処理
//==========================
HRESULT CTutorialManager::Init(void)
{
	// シリンダー生成
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 550.0f);

	// ドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

	// ドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);

	// フィールド生成
	CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

	// プレイヤー生成
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 0, "data\\MOTION\\Player\\TutoPlayer100motion.txt");
	CPlayer::Create(VECTOR3_NULL, VECTOR3_NULL, 10, 1, "data\\MOTION\\Player\\TutoPlayer200motion.txt");

	//地面ブロック配置
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

	// 生成
	CTutorialBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f));

	// タスク生成
	m_pTask = new CTutoTask;

	// nullじゃなかったら
	if (m_pTask != nullptr)
	{
		// 初期化処理
		m_pTask->Init();
	}

	// 初期化結果を返す
	return S_OK;
}
//==========================
// 終了処理
//==========================
void CTutorialManager::Uninit(void)
{
	// nullじゃなかったら
	if (m_pTask != nullptr)
	{
		// 終了処理
		m_pTask->Uninit();

		// 破棄
		delete m_pTask;

		// null初期化
		m_pTask = nullptr;
	}
}
//==========================
// 更新処理
//==========================
void CTutorialManager::Update(void)
{
	// タスククラスの更新処理
	if (m_pTask != nullptr)
	{
		m_pTask->Update();
	}

	// 入力デバイス取得
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// 取得失敗時
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// 番号取得
	int nIdx = m_pTask->GetTaskIndex();

	// 管理フラグ
	bool isCheck = false;
	bool isFinish = false;
	static bool isJump = false;

	// 現在番号に応じて変更
	switch (nIdx)
	{
	case CTutorialManager::TASKTYPE_MOVE:	// 移動入力
		if ((pKey->GetPress(DIK_A) || pKey->GetPress(DIK_D)) ||
			(pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_RIGHT)))
		{
			isCheck = true;
		}

		break;

	case CTutorialManager::TASKTYPE_ATTACK:	// 攻撃入力

		if ((pKey->GetPress(DIK_RETURN) || pJoyPad->GetPress(pJoyPad->JOYKEY_X)))
		{
			isCheck = true;
		}

		break;
	case CTutorialManager::TASKTYPE_JUMP:	// ジャンプ入力

		if ((pKey->GetTrigger(DIK_SPACE) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A)))
		{
			isCheck = true;
		}

		break;

	case CTutorialManager::TASKTYPE_JUMPATTACK: // ジャンプ攻撃

		// ジャンプしたらフラグを立てる
		if (pKey->GetTrigger(DIK_SPACE) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A))
		{
			isJump = true;
		}

		// ジャンプ済みフラグがある状態で攻撃
		if (isJump && (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_X)))
		{
			isCheck = true;
			isJump = false; // 一度判定取ったらリセット
		}

		break;

	case CTutorialManager::TASKTYPE_LASER: // 武器切り替え

		if ((pKey->GetTrigger(DIK_F) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT_B)))
		{
			isCheck = true;
		}

		break;

	default:

		break;
	}

	// 入力が有効時,次に進む
	if (isCheck)
	{
		m_pTask->NextTask();
	}

	// 決定キー入力 or パッドのstartボタン かつ 終了フラグが有効なら
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && isFinish)
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();

		// ゲームシーンに遷移
		if (pFade != nullptr) pFade->SetFade(new CGame());
	}
}