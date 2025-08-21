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
	// ui生成
	m_pTutoui = CTutorialUi::Create(D3DXVECTOR3(500.0f, 200.0f, 0.0f), 300.0f, 60.0f, 0);

	// プレイヤー生成
	
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
	if (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START))
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();

		// ゲームシーンに遷移
		if (pFade != nullptr) pFade->SetFade(new CGame());
	}
}
