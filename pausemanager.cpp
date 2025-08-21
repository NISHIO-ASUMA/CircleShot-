//=====================================
//
// ポーズ管理処理 [ pausemanager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "pausemanager.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "title.h"
#include "game.h"

//***************************
// 静的メンバ変数宣言
//***************************
bool CPauseManager::m_isPause = false; // ポーズフラグ

//==================================
// コンストラクタ
//==================================
CPauseManager::CPauseManager()
{
	// 値のクリア
	m_nSelectIdx = NULL;
	m_isPause = false;

	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
	{
		m_pPause[nCnt] = nullptr;
	}
}
//==================================
// デストラクタ
//==================================
CPauseManager::~CPauseManager()
{
	// 無し
}
//==================================
// 初期化処理
//==================================
HRESULT CPauseManager::Init(void)
{
	// 初期セレクト番号設定
	m_nSelectIdx = CPause::MENU_RETRY;

	// 基準座標を設定
	D3DXVECTOR3 Bacepos = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	
	// ポーズ生成
	for (int nPause = 0; nPause < SELECT_MAX; nPause++)
	{
		// 座標セット
		D3DXVECTOR3 pos = Bacepos;

		// 高さを空ける
		pos.y += nPause * SPACEHEIGHT;

		// ポーズUIを生成 
		if (nPause == CPause::MENU_BACK)
		{
			// 背景生成
			m_pPause[nPause] = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f,0.0f), SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, COLOR_WHITE, nPause);
		}
		else
		{
			// 選択用ポリゴンの生成
			m_pPause[nPause] = CPause::Create(pos, 180.0f, 40.0f, COLOR_WHITE, nPause);
		}
	}

	// 初期化結果を返す
	return S_OK;
}
//==================================
// 終了処理
//==================================
void CPauseManager::Uninit(void)
{
	// 無し
}
//==================================
// 更新処理
//==================================
void CPauseManager::Update(void)
{
	// ポーズ中じゃなかったら
	if (m_isPause == false)
	{
		// ここで処理を返す
		return;
	}

	// 入力デバイス取得
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// nullチェック
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// nullだったら
	if (pSound == nullptr) return;

	// 選択インデックス範囲
	const int SELECT_BEGIN = 1;
	const int SELECT_END = SELECT_MAX - 1;

	// 上キー入力
	if (pKey->GetTrigger(DIK_UP) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_UP))
	{
		// サウンド再生
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// インデックス番号を減算
		m_nSelectIdx--;

		// 最小値以下なら最小値に設定
		if (m_nSelectIdx < SELECT_BEGIN)
			m_nSelectIdx = SELECT_END;
	}

	// 下キー入力
	if (pKey->GetTrigger(DIK_DOWN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_DOWN))
	{
		// サウンド再生
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// インデックス番号を加算
		m_nSelectIdx++;

		// 最大値以上なら最大値に設定
		if (m_nSelectIdx > SELECT_END)
			m_nSelectIdx = SELECT_BEGIN;
	}

	// フェード取得
	CFade* pFade = CManager::GetFade();

	// nullだったら
	if (pFade == nullptr) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// nullだったら
	if (pCamera == nullptr) return;

	// 選択されているメニューのポリゴンカラーを変更
	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
	{
		// 背景は変えない
		if (nCnt == CPause::MENU_BACK) continue;

		// nullじゃなかったら
		if (m_pPause[nCnt] != nullptr)
		{
			// カラー変更
			if (nCnt == m_nSelectIdx)
				m_pPause[nCnt]->SetCol(COLOR_YERROW);	// 黄色
			else
				m_pPause[nCnt]->SetCol(COLOR_WHITE);	// 白
		}
	}

	// 決定処理
	if (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A))
	{
		// サウンド再生
		pSound->PlaySound(pSound->SOUND_LABEL_RETURN);

		switch (m_nSelectIdx)
		{
		case CPause::MENU_BACK:	// 背景
			break;

		case CPause::MENU_RETRY:	// リトライ時
			if (pFade != nullptr) pFade->SetFade(new CGame());	// ゲームシーンに遷移
			SetEnablePause(false);	// ポーズ終了
			break;

		case CPause::MENU_CONTINUE:	// コンテニュー時
			SetEnablePause(false);	// ポーズ終了
			break;

		case CPause::MENU_QUIT:		// 退出時
			if (pFade != nullptr) pFade->SetFade(new CTitle(true));	// タイトルシーンに遷移
			SetEnablePause(false);	// ポーズ終了

			// カメラの設定を初期化する
			pCamera->SetFinishRotation(false);
			pCamera->SetIsRotation(false);
			break;
		}
	}
}
//===========================
// ポーズかどうか
//===========================
void CPauseManager::SetEnablePause(void)
{
	//  Pキーが押された
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_P))
	{
		// フラグ変更
		m_isPause = m_isPause ? false : true;
	}
}