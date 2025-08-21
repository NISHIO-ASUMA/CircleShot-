//====================================
//
// タイトル処理 [ title.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "title.h"
#include "manager.h"
#include "game.h"
#include "ui.h"
#include "titlemanager.h"

//=====================================
// コンストラクタ
//=====================================
CTitle::CTitle(bool isFirst) : CScene(CScene::MODE_TITLE), m_isCreate(isFirst)
{
	//無し
}
//=====================================
// デストラクタ
//=====================================
CTitle::~CTitle()
{
	// 無し
}
//=====================================
// 初期化処理
//=====================================
HRESULT CTitle::Init(void)
{
	// インスタンス生成
	m_pTitleManager = new CTitleManager(m_isCreate);

	// 生成失敗時
	if (m_pTitleManager == nullptr) return E_FAIL;

	// マネージャーの初期化処理
	m_pTitleManager->Init();

	// 初期化結果を返す
	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CTitle::Uninit(void)
{
	// nullチェック
	if (m_pTitleManager != nullptr)
	{
		// 終了処理
		m_pTitleManager->Uninit();

		// 破棄
		delete m_pTitleManager;

		// nullptrする
		m_pTitleManager = nullptr;
	}
}
//=====================================
// 更新処理
//=====================================
void CTitle::Update(void)
{
	// nullじゃなかったら
	if (m_pTitleManager != nullptr)
	{
		// マネージャーの更新処理
		m_pTitleManager->Update();
	}
}
//=====================================
// 描画処理
//=====================================
void CTitle::Draw(void)
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CTitle* CTitle::Create(bool isFirst)
{
	// インスタンス生成
	CTitle* pTitle = new CTitle(isFirst);

	// nullだったら
	if (pTitle == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pTitle;
}
