//=============================================
//
// チュートリアルUI処理 [ tutorialui.cpp ]
// Author: Asuma Nishio
//
//=============================================

//******************************
// インクルードファイル宣言
//******************************
#include "tutorialui.h"
#include "manager.h"
#include "texture.h"

//==============================
// コンストラクタ
//==============================
CTutorialUi::CTutorialUi()
{
	// 値のクリア
	m_nIdxTexture = NULL;
}
//==============================
// デストラクタ
//==============================
CTutorialUi::~CTutorialUi()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CTutorialUi* CTutorialUi::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType)
{
	// インスタンス生成
	CTutorialUi* pTutoUi = new CTutorialUi;

	// インスタンス生成失敗時
	if (pTutoUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTutoUi->Init()))
	{
		return nullptr;
	}

	// オブジェクト2Dの基本設定
	pTutoUi->SetPos(pos);
	pTutoUi->SetSize(fWidth, fHeight);
	pTutoUi->SetTexture(nType);

	// 生成されたポインタを返す
	return pTutoUi;
}
//==============================
// 初期化処理
//==============================
HRESULT CTutorialUi::Init(void)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	// 頂点生成タイプを設定
	SetAnchor(CObject2D::ANCHORTYPE_CENTER);

	// 初期化結果を返す
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CTutorialUi::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}
//==============================
// 更新処理
//==============================
void CTutorialUi::Update(void)
{
	// オブジェクト2Dの更新処理
	CObject2D::Update();
}
//==============================
// 描画処理
//==============================
void CTutorialUi::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャポインタ取得
	CTexture * pTexture = CManager::GetTexture();

	// 取得時,nullだったら
	if (pTexture == nullptr) return;

	// 割り当て
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// オブジェクト2Dの描画処理
	CObject2D::Draw();
}
//==============================
// テクスチャ割り当て処理
//==============================
void CTutorialUi::SetTexture(int nType)
{
	// テクスチャポインタを取得
	CTexture* pTexture = CManager::GetTexture();

	// 取得時,nullだったら
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case 0:
		// テクスチャ割り当て
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\tutorial_menu.png");
		break;

	default:

		break;
	}
}
