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

//==========================
// コンストラクタ
//==========================
CTutorialManager::CTutorialManager()
{
	// 値のクリア
	m_pTutoui = nullptr;
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

	// 初期化結果を返す
	return S_OK;
}
//==========================
// 終了処理
//==========================
void CTutorialManager::Uninit(void)
{
	// 無し
}
//==========================
// 更新処理
//==========================
void CTutorialManager::Update(void)
{
	// 入力デバイス取得
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// 取得失敗時
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// 決定キー入力 or パッドのstartボタン
	if (pKey->GetTrigger(DIK_P) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START))
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();

		// ゲームシーンに遷移
		if (pFade != nullptr) pFade->SetFade(new CGame());
	}
}
