//====================================
//
// リザルトシーン処理 [ result.cpp ]
// Author: Asuma Nishio
// 
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "result.h"
#include "resultmanager.h"

//=================================
// オーバーロードコンストラクタ
//=================================
CResult::CResult() : CScene(CScene::MODE_RESULT)
{
	// 値のクリア
	m_pResultManager = nullptr;
}
//=================================
// デストラクタ
//=================================
CResult::~CResult()
{
	// 無し
}
//=================================
// 生成処理
//=================================
CResult* CResult::Create(void)
{
	// インスタンス生成
	CResult* pResult = new CResult;

	// 生成に失敗したら
	if (pResult == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pResult->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pResult;
}
//=================================
// 初期化処理
//=================================
HRESULT CResult::Init(void)
{
	// マネージャーのインスタンス生成
	m_pResultManager = new CResultManager;

	// 生成に失敗したら
	if (m_pResultManager == nullptr) return E_FAIL;
	
	// マネージャーの初期化処理
	m_pResultManager->Init();


	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CResult::Uninit(void)
{
	 // nullチェック
	 if (m_pResultManager != nullptr)
	 {
		// 終了処理
		m_pResultManager->Uninit();

		// ポインタの破棄
		delete m_pResultManager;

		// nullに設定
		m_pResultManager = nullptr;
	 }
}
//=================================
// 更新処理
//=================================
void CResult::Update(void)
{
	// nullじゃなかったら
	if (m_pResultManager != nullptr)
	{
		// リザルトマネージャーの更新
		m_pResultManager->Update();
	}
}
//=================================
// 描画処理
//=================================
void CResult::Draw(void)
{
	// 無し
}
