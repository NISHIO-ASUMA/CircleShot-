//=========================================
//
// タイトル管理処理 [ titlemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// インクルードファイル宣言
//***************************
#include "titlemanager.h"
#include "titleui.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "input.h"
#include "block.h"
#include "meshfield.h"
#include "meshdome.h"
#include "titleplayer.h"
#include "ui.h"
#include "sound.h"
#include "titlelogo.h"

//============================
// コンストラクタ
//============================
CTitleManager::CTitleManager(bool isCreate) : m_isFirstuiCreate(isCreate)
{
	// 値のクリア
	m_nIdx = NULL;

	for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
	{
		m_pTitleui[nCnt] = nullptr;
	}

	m_isuiCreate = false;
}
//============================
// デストラクタ
//============================
CTitleManager::~CTitleManager()
{
	// 無し
}
//============================
// 初期化処理
//============================
HRESULT CTitleManager::Init(void)
{	
	// 他のシーン等から戻ってきたとき
	if (!m_isFirstuiCreate) 
	{
		// 基準座標を設定
		D3DXVECTOR3 CenterPos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 480.0f, 0.0f);

		// タイトルのuiを生成
		for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
		{
			// 高さの間隔空ける
			CenterPos.y += nCnt * DIGITPOS;

			// uiを生成 ( 選択メニュー分 )
			m_pTitleui[nCnt] = CTitleUi::Create(CenterPos, COLOR_WHITE, UIWIDTH, UIHEIGHT, nCnt);
		}

		// フラグを有効化
		m_isuiCreate = true;
	}

	// 地面生成
	CMeshField::Create(VECTOR3_NULL, FIELDWIDTH);

	// 球状メッシュを生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 500.0f);

	// タイトルプレイヤーを生成
	CTitlePlayer::Create(D3DXVECTOR3(180.0f,0.0f,0.0f),VECTOR3_NULL, 0, "data\\MOTION\\Player\\TitlePlayer100.txt");
	CTitlePlayer::Create(D3DXVECTOR3(260.0f,0.0f,0.0f),VECTOR3_NULL, 1, "data\\MOTION\\Player\\TitlePlayer200.txt");

	// ロゴ生成
	CTitleLogo::Create(D3DXVECTOR3(200.0f, 90.0f, 0.0f), 200.0f, 60.0f, 1);

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// nullだったら
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->PlaySound(CSound::SOUND_LABEL_TITLE_BGM);

	// 初期化結果を返す
	return S_OK;
}
//============================
// 終了処理
//============================
void CTitleManager::Uninit(void)
{
	// 無し
}
//============================
// 更新処理
//============================
void CTitleManager::Update(void)
{
	// 入力デバイス取得
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// 取得失敗時
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// nullだったら
	if (pSound == nullptr) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// 取得失敗時
	if (pCamera == nullptr) return;

	// キー入力時 かつ uiが生成されていなかったら
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A)) && !m_isuiCreate)
	{
		// 基準座標を設定
		D3DXVECTOR3 CenterPos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 480.0f, 0.0f);

		// タイトルのuiを生成
		for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
		{
			// 高さの間隔空ける
			CenterPos.y += nCnt * DIGITPOS;

			// uiを生成 ( 選択メニュー分 )
			m_pTitleui[nCnt] = CTitleUi::Create(CenterPos, COLOR_WHITE, UIWIDTH, UIHEIGHT, nCnt);
		}

		// フラグを有効化
		m_isuiCreate = true;
	}

	// 選択インデックス範囲
	const int SELECT_BEGIN = NULL;
	const int SELECT_END = TITLE_MENU -1;

	// 上キー入力
	if (pKey->GetTrigger(DIK_UP) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_UP))
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// インデックス番号を減算
		m_nIdx--;

		// 最小値以下なら最小値に設定
		if (m_nIdx < SELECT_BEGIN)
			m_nIdx = SELECT_END;
	}

	// 下キー入力
	if (pKey->GetTrigger(DIK_DOWN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_DOWN))
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// インデックス番号を加算
		m_nIdx++;

		// 最大値以上なら最大値に設定
		if (m_nIdx > SELECT_END)
			m_nIdx = SELECT_BEGIN;
	}

	// フェード取得
	CFade* pFade = CManager::GetFade();

	// nullだったら
	if (pFade == nullptr) return;

	// 選択されているメニューのポリゴンカラーを変更
	for (int nCnt = 0; nCnt < TITLE_MENU; nCnt++)
	{
		// nullじゃなかったら
		if (m_pTitleui[nCnt] != nullptr)
		{
			// カラー変更
			if (nCnt == m_nIdx)
			{
				// カラーセット
				m_pTitleui[nCnt]->SetCol(COLOR_YERROW);
			}
			else
			{
				// カラーセット
				m_pTitleui[nCnt]->SetCol(COLOR_WHITE);
			}
		}
	}

	// 決定処理
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A)) && pCamera->GetFinishRotation())
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_RETURN);

		switch (m_nIdx)
		{
		case CTitleUi::MENU_GAME:		// ゲームモード
			if (pFade != nullptr) pFade->SetFade(new CGame());	// ゲームシーンに遷移
			break;

		case CTitleUi::MENU_TUTORIAL:	// チュートリアルモード
			if (pFade != nullptr) pFade->SetFade(new CTutorial());	// チュートリアルシーンに遷移
			break;

		default:
			break;
		}
	}
}