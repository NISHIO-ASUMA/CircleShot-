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
#include "resultscore.h"
#include "ui.h"

//=================================
// コンストラクタ
//=================================
CResultManager::CResultManager()
{
	// 値のクリア
	m_isKeyDown = false;
	m_nGameScore = NULL;
	m_nLastTime = NULL;

	for (int nCnt = 0; nCnt < SCORELISTNUM; nCnt++)
	{
		m_pResultScore[nCnt] = nullptr;
	}
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
	// UI生成
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "data\\TEXTURE\\resultback.jpg", false);

	// データの読み込み
	Load();

	// スコアを生成する
	m_pResultScore[0] = CResultScore::Create(D3DXVECTOR3(1120.0f, 260.0f, 0.0f), 300.0f, 60.0f,0);
	m_pResultScore[1] = CResultScore::Create(D3DXVECTOR3(1120.0f, 415.0f, 0.0f), 300.0f, 60.0f,1);
	m_pResultScore[2] = CResultScore::Create(D3DXVECTOR3(1120.0f, 600.0f, 0.0f), 300.0f, 60.0f,2);

	// 討伐スコア
	m_pResultScore[0]->SetScore(m_nGameScore);

	// タイムスコア
	m_pResultScore[1]->SetTimeScore(m_nLastTime);
	int nScore = m_pResultScore[1]->MathTimescore();
	m_pResultScore[1]->SetTimeScore(nScore);

	// 最終スコア
	m_pResultScore[2]->SetLastScore(m_nGameScore, nScore);


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
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)))
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
//=================================
// 更新処理
//=================================
void CResultManager::Load(void)
{
	// 読み取った値を格納するメンバ変数
	m_nGameScore = 0;
	m_nLastTime = 0;

	//==============================
	// GameScore.txt
	//==============================
	{
		std::ifstream file("data\\Loader\\GameScore.txt");

		if (file.is_open())
		{
			file >> m_nGameScore;   // 数値1個を読み取り
			file.close();
		}
		else
		{
			MessageBox(NULL, "GameScore.txt が開けませんでした", "エラー", MB_OK);
		}
	}

	//==============================
	// LastTime.txt
	//==============================
	{
		std::ifstream file("data\\Loader\\LastTime.txt");
		if (file.is_open())
		{
			file >> m_nLastTime;    // 数値1個を読み取り
			file.close();
		}
		else
		{
			MessageBox(NULL, "LastTime.txt が開けませんでした", "エラー", MB_OK);
		}
	}
}
