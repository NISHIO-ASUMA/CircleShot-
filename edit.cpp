//========================================
//
// エディターシーン処理 [ edit.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// インクルードファイル
//**********************************
#include "edit.h"
#include "editmanager.h"

//================================
// オーバーロードコンストラクタ
//================================
CEdit::CEdit() : CScene(CScene::MODE_EDIT)
{
	// 値のクリア
	m_pEditManager = nullptr;
}
//================================
// デストラクタ
//================================
CEdit::~CEdit()
{
	// 無し
}
//================================
// 生成処理
//================================
CEdit* CEdit::Create(void)
{
	// インスタンス生成
	CEdit* pEdit = new CEdit;

	// nullなら
	if (pEdit == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pEdit->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pEdit;
}
//================================
// 初期化処理
//================================
HRESULT CEdit::Init(void)
{
	// マネージャーのインスタンス生成
	m_pEditManager = new CEditManager;

	// nullじゃなかったら
	if (m_pEditManager != nullptr)
	{
		// 初期化処理
		m_pEditManager->Init();
	}

	// 初期化結果を返す
	return S_OK;
}
//================================
// 終了処理
//================================
void CEdit::Uninit(void)
{
	// nullじゃなかったら
	if (m_pEditManager != nullptr)
	{
		// マネージャーの終了処理
		m_pEditManager->Uninit();

		// ポインタの破棄
		delete m_pEditManager;

		// null初期化
		m_pEditManager = nullptr;
	}
}
//================================
// 更新処理
//================================
void CEdit::Update(void)
{
	// nullじゃなかったら
	if (m_pEditManager != nullptr)
	{
		// マネージャーの更新処理
		m_pEditManager->Update();
	}
}
//================================
// 描画処理
//================================
void CEdit::Draw(void)
{
	// 無し
}
