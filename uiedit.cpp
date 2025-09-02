//=====================================
//
// エディター処理 [ uiedit.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "uiedit.h"
#include "ui.h"
#include "uieditmanager.h"

//===============================
// コンストラクタ
//===============================
CUiedit::CUiedit() : CScene(CScene::MODE_UIEDIT)
{
	// 値のクリア
	m_pUiEditManager = nullptr;
}
//===============================
// デストラクタ
//===============================
CUiedit::~CUiedit()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CUiedit::Init(void)
{
	// メモリ確保
	m_pUiEditManager = new CUiEditManager;

	// nullなら
	if (m_pUiEditManager == nullptr) return E_FAIL;

	// 初期化処理
	m_pUiEditManager->Init();

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CUiedit::Uninit(void)
{
	// nullチェック
	if (m_pUiEditManager != nullptr)
	{
		// 終了処理
		m_pUiEditManager->Uninit();

		// ポインタの破棄
		delete m_pUiEditManager;

		// null初期化
		m_pUiEditManager = nullptr;
	}
}
//===============================
// 更新処理
//===============================
void CUiedit::Update(void)
{
	// nullじゃなかったら
	if (m_pUiEditManager != nullptr)
	{
		m_pUiEditManager->Update();
	}
}
//===============================
// 描画処理
//===============================
void CUiedit::Draw(void)
{
	// nullじゃなかったら
	if (m_pUiEditManager != nullptr)
	{
		m_pUiEditManager->Draw();
	}
}
//===============================
// 生成処理
//===============================
CUiedit* CUiedit::Create(void)
{
	// インスタンス生成
	CUiedit* pUiEdit = new CUiedit;

	// nullチェック
	if (pUiEdit == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pUiEdit->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタ
	return pUiEdit;
}
