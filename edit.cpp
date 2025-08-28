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
#include "meshdome.h"
#include "meshfield.h"
#include "block.h"

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
	// ドーム生成
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

	// フィールド生成
	CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

	// ブロック配置
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f);

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
	// nullじゃなかったら
	if (m_pEditManager != nullptr)
	{
		// マネージャーの描画
		m_pEditManager->Draw();
	}
}