//==========================================
//
// タイトル管理処理 [ titlemanager.cpp ]
// Author: Asuma Nishio
// 
// 
// TODO : カメラ回転させないでいい
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
#include "edit.h"
#include "pausemanager.h"
#include "pointui.h"
#include "sceneloader.h"
#include "tutorialboss.h"

//*************************
// 名前空間
//*************************
namespace TITLEMANAGERINFO
{
	const D3DXVECTOR3 m_BacePos = { 210.0f, 520.0f, 0.0f };	// 基準座標
};

//============================
// コンストラクタ
//============================
CTitleManager::CTitleManager(bool isCreate) : m_isFirstuiCreate(isCreate)
{
	// 値のクリア
	m_nIdx = NULL;
	m_Info = {};

	for (int nCnt = 0; nCnt < TITLEINFO::TITLE_MENU; nCnt++)
	{
		m_pTitleui[nCnt] = nullptr;
	}
	m_pPointUi = nullptr;
	m_pUi = nullptr;
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
	// シーンテキスト読み込み
	CSceneLoader::SplitLoad(0);

	// 他のシーン等から戻ってきたとき
	if (!m_isFirstuiCreate) 
	{
		// タイトルのuiを生成
		for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
		{
			// 横の間隔を空ける
			D3DXVECTOR3 pos = TITLEMANAGERINFO::m_BacePos;

			pos.x += nCnt * m_Info.INTERVAL;

			// uiを生成
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, m_Info.UIWIDTH, m_Info.UIHEIGHT, nCnt);
		}

		// フラグを有効化
		m_isuiCreate = true;
	}

	// タイトルプレイヤーを生成
	CTitlePlayer::Create(D3DXVECTOR3(-40.0f,0.0f,-550.0f),VECTOR3_NULL, 0, "data\\MOTION\\Player\\TitlePlayer100.txt");
	CTitlePlayer::Create(D3DXVECTOR3(40.0f,0.0f,-550.0f), VECTOR3_NULL, 1, "data\\MOTION\\Player\\TitlePlayer200.txt");

	// タイトルロゴ生成
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f), 365.0f, 100.0f);

	// 初期UI生成
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f),30, 200.0f, 60.0f, "data\\TEXTURE\\Enterkey.png", true);

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
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && !m_isuiCreate)
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_RETURN);

		// 点滅停止
		m_pUi->SetUseFall(false,CUi::STATE_FALL);

		// UI生成
		CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 660.0f, 0.0f), 0, 520.0f,55.0f, "data\\TEXTURE\\title_menuselect.png", false);

		// タイトルのuiを生成
		for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
		{
			// 横の間隔を空ける
			D3DXVECTOR3 pos = TITLEMANAGERINFO::m_BacePos;

			pos.x += nCnt * m_Info.INTERVAL;

			// uiを生成
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, m_Info.UIWIDTH, m_Info.UIHEIGHT, nCnt);
		}

		// nullなら
		if (!m_pPointUi)
		{
			// 最初は選択中のUI位置
			D3DXVECTOR3 pos = m_pTitleui[m_nIdx]->GetPos(); 

			// 選択メニューの上に生成
			pos.y -= m_Info.SELECTPOS;

			// 矢印UI生成
			m_pPointUi = CPointUi::Create(pos);
		}

		// フラグを有効化
		m_isuiCreate = true;
	}

	// 横キー入力
	if (pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT) || pKey->GetTrigger(DIK_A) && m_isuiCreate)
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// インデックス番号を減算
		m_nIdx--;

		// 最小値以下なら最小値に設定
		if (m_nIdx < m_Info.SELECT_START)
			m_nIdx = m_Info.SELECT_END;
	}

	// 横キー入力
	if (pJoyPad->GetTrigger(pJoyPad->JOYKEY_RIGHT) || pKey->GetTrigger(DIK_D) && m_isuiCreate)
	{
		// サウンド再生
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// インデックス番号を加算
		m_nIdx++;

		// 最大値以上なら最大値に設定
		if (m_nIdx > m_Info.SELECT_END)
			m_nIdx = m_Info.SELECT_START;
	}

	// フェード取得
	CFade* pFade = CManager::GetFade();

	// nullだったら
	if (pFade == nullptr) return;

	// 選択されているメニューのポリゴンカラーを変更
	for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
	{
		// nullじゃなかったら
		if (m_pTitleui[nCnt] != nullptr)
		{
			// カラー変更
			if (nCnt == m_nIdx)
			{// 選択されているもの
				// カラーセット
				m_pTitleui[nCnt]->SetFlash(NULL, 10, COLOR_WHITE);

				// 少し大きくする
				m_pTitleui[nCnt]->SetSize(m_Info.SPREADWIDTH, m_Info.SPREADHEIGHT);
			}
			else
			{// 選択されたいないもの
				// カラーセット
				m_pTitleui[nCnt]->SetCol(COLOR_WHITE);

				// いつものサイズ
				m_pTitleui[nCnt]->SetSize(m_Info.UIWIDTH, m_Info.UIHEIGHT);
			}
		}
	}

	// nullじゃなかったら
	if (m_pPointUi && m_pTitleui[m_nIdx])
	{
		// 座標主h得
		D3DXVECTOR3 pos = m_pTitleui[m_nIdx]->GetPos();

		// 上にセット
		pos.y -= m_Info.SELECTPOS;

		// 座標を合わせる
		m_pPointUi->SetPos(pos);
	}

	// Enterキー or Startボタン
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && pCamera->GetIsRotation() && pCamera->GetKeyFlag())
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

		case CTitleUi::MENU_EXIT:	// 終了メニュー
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}

#ifdef _DEBUG

	// F2キー
	if ((pKey->GetTrigger(DIK_F9)))
	{
		// 編集画面
		if (pFade != nullptr) pFade->SetFade(new CEdit());
	}

#endif // _DEBUG

}