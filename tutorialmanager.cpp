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
#include "effectpiler.h"
#include "exitpoint.h"
#include "block.h"
#include "charge.h"

//==========================
// コンストラクタ
//==========================
CTutorialManager::CTutorialManager()
{
	// 値のクリア
	m_pTutoui = nullptr;
	m_pTask = nullptr;
	m_isFreeDone = false;
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
	// シーンテキスト読み込み
	CSceneLoader::SplitLoad(1);

	// ボス生成
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
	static bool isFinish = false;
	static bool isJump = false;
	static bool isLaserActionDone = false;

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

		// チャージ加算
		CCharge::AddCharge(100.0f);

		// フラグ有効化　かつ キー入力
		if ((pKey->GetTrigger(DIK_F) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT_B)) && CCharge::GetChargeFlag())
		{
			isCheck = true;
		}
		break;

	case CTutorialManager::TASKTYPE_LASERACTION: // レーザー攻撃

		// キー入力している
		if (pKey->GetPress(DIK_RETURN) || pJoyPad->GetPress(pJoyPad->JOYKEY_X))
		{
			// 減算
			CCharge::DecCharge(0.5f);
		}

		if (!CCharge::GetChargeFlag() && !isLaserActionDone)
		{
			isCheck = true;
			isLaserActionDone = true;
		}

		break;

	case CTutorialManager::TASKTYPE_FREE: // フリー
		if (!m_isFreeDone)  // まだ処理してないときだけ
		{
			isFinish = true;
			m_isFreeDone = true; // 1回処理したらロック
		}
		break;

	default:
		break;
	}

	if (isFinish)
	{
		// ポイント生成
		CExitPoint::Create(D3DXVECTOR3(0.0f, 0.0f, -550.0f), 0.5f);

		// ブロック生成
		CBlock::Create("data\\MODEL\\STAGEOBJ\\yajirusi.x", D3DXVECTOR3(0.0f, 180.0f, -550.0f), D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f), 0.0f,1);
		CBlock::Create("data\\MODEL\\STAGEOBJ\\Billboard_kanban.x", D3DXVECTOR3(0.0f, 190.0f, -550.0f), VECTOR3_NULL, 0.0f, 0);

		// 無効化する
		isFinish = false;
	}

	// 入力が有効時
	if (isCheck)
	{
		// サウンド再生
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_CLEAR);

		// 次に進む
		m_pTask->NextTask();
	}
}