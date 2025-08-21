//====================================
//
// タイトルui処理 [ titleui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "titleui.h"
#include "texture.h"
#include "manager.h"

//=========================
// コンストラクタ
//=========================
CTitleUi::CTitleUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nTexIdx = NULL;
}
//=========================
// デストラクタ
//=========================
CTitleUi::~CTitleUi()
{
	// 無い
}
//=========================
// 初期化処理
//=========================
HRESULT CTitleUi::Init(void)
{
	// 2Dオブジェクトの初期化処理
	CObject2D::Init();

	// 頂点タイプを設定
	SetAnchor(ANCHORTYPE_CENTER);

	// 初期化結果を返す
	return S_OK;
}
//=========================
// 終了処理
//=========================
void CTitleUi::Uninit(void)
{
	// 2Dオブジェクトの終了処理
	CObject2D::Uninit();
}
//=========================
// 更新処理
//=========================
void CTitleUi::Update(void)
{
	// 2Dオブジェクトの更新処理
	CObject2D::Update();
}
//=========================
// 描画処理
//=========================
void CTitleUi::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullだったらここで処理終了
	if (pTexture == nullptr) return;

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// 2Dオブジェクトの描画処理
	CObject2D::Draw();
}
//=========================
// 生成処理
//=========================
CTitleUi* CTitleUi::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType)
{
	// インスタンス生成
	CTitleUi* pTitleui = new CTitleUi;

	// nullだったら
	if (pTitleui == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTitleui->Init())) 
	{
		// nullを返す
		return nullptr;
	}

	// 2Dオブジェクト設定
	pTitleui->SetPos(pos);
	pTitleui->SetCol(col);
	pTitleui->SetSize(fWidth, fHeight);
	pTitleui->SetTexture(nType);

	// 生成されたポインタを返す
	return pTitleui;
}
//=========================
// テクスチャ割り当て処理
//=========================
void CTitleUi::SetTexture(int nType)
{
	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullだったらここで処理終了
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case MENU_GAME:			// ゲームメニュー
		m_nTexIdx = pTexture->Register("data\\TEXTURE\\titlemenu001.png");
		break;

	case MENU_TUTORIAL:		// チュートリアルメニュー
		m_nTexIdx = pTexture->Register("data\\TEXTURE\\titilemenu_002.png");
		break;

	default:
		m_nTexIdx = -1;
		break;
	}

}
