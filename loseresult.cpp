//============================================
//
// 負けリザルトシーン処理 [ loseresult.cpp ]
// Author: Asuma Nishio
// 
//============================================

//**************************
// インクルードファイル宣言
//**************************
#include "loseresult.h"
#include "manager.h"
#include "ui.h"
#include "title.h"
#include "sound.h"

//===============================
// コンストラクタ
//===============================
CLoseResult::CLoseResult() : CScene(CScene::MODE_LOSERESULT)
{
	// 値のクリア
}
//===============================
// デストラクタ
//===============================
CLoseResult::~CLoseResult()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CLoseResult* CLoseResult::Create(void)
{
	// インスタンス生成
	CLoseResult* pLoseresult = new CLoseResult;
	if (pLoseresult == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pLoseresult->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pLoseresult;
}
//===============================
// 初期化処理
//===============================
HRESULT CLoseResult::Init(void)
{
	// UI生成
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "data\\TEXTURE\\LoseResult.jpg",false);

	// サウンド取得
	CSound* pSound = CManager::GetSound();
	if (pSound == nullptr) return E_FAIL;

	// サウンド再生
	pSound->PlaySound(CSound::SOUND_LABEL_LOSERESULTBGM);

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CLoseResult::Uninit(void)
{
	// 無し
}
//===============================
// 更新処理
//===============================
void CLoseResult::Update(void)
{
	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

	// キー入力でタイトルに戻る
	if ((CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CManager::GetJoyPad()->JOYKEY_A)))
	{
		// ポインタ取得
		CFade* pFade = CManager::GetFade();

		// nullじゃないとき
		if (pFade != nullptr)
		{
			// シーン遷移
			pFade->SetFade(new CTitle(true));

			// カメラ初期化
			pCamera->Init();

			// カメラの設定を初期化する
			pCamera->SetFinishRotation(false);
			pCamera->SetIsRotation(false);
			pCamera->SetKey(false);

			return;
		}
	}
}
//===============================
// 描画処理
//===============================
void CLoseResult::Draw(void)
{
	// 無し
}
