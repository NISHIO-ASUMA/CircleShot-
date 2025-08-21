//==============================================
//
// リザルトシーン管理処理 [ resultmanager.cpp ]
// Author: Asuma Nishio
// 
//==============================================

//**************************
// インクルードファイル宣言
//**************************
#include "resultmanager.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "resultui.h"

//=================================
// コンストラクタ
//=================================
CResultManager::CResultManager()
{
	// 値のクリア
	m_isKeyDown = false;
}
//=================================
// デストラクタ
//=================================
CResultManager::~CResultManager()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CResultManager::Init(void)
{	
	// ui生成
	CResultUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 360.0f, 0.0f), COLOR_WHITE, 350.0f, 200.0f, 0);

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// nullだったら
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->PlaySound(CSound::SOUND_LABEL_RESULTBGM);

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CResultManager::Uninit(void)
{
	// nullチェック

}
//=================================
// 更新処理
//=================================
void CResultManager::Update(void)
{
	// 入力デバイスを取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pJyoPad = CManager::GetJoyPad();

	// 取得失敗時
	if (pInput == nullptr) return;
	if (pJyoPad == nullptr) return;

	// カメラを取得
	CCamera* pCamera = CManager::GetCamera();

	// 取得失敗時
	if (pCamera == nullptr) return;

	// 決定キーが押された
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)) && !m_isKeyDown)
	{
		// ポインタ取得
		CFade* pFade = CManager::GetFade();

		// nullじゃないとき
		if (pFade != nullptr)
		{
			// フラグ有効化
			m_isKeyDown = true;

			// シーン遷移
			pFade->SetFade(new CTitle(true));

			// カメラの設定を初期化する
			pCamera->SetFinishRotation(false);
			pCamera->SetIsRotation(false);

			return;

		}
	}
}
