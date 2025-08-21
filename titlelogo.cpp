//=========================================
//
// タイトルロゴ処理 [ titlelogo.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// インクルードファイル宣言
//***************************
#include "titlelogo.h"
#include "manager.h"
#include "texture.h"

//================================
// オーバーロードコンストラクタ
//================================
CTitleLogo::CTitleLogo(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nTexIdx = NULL;
}
//================================
// デストラクタ
//================================
CTitleLogo::~CTitleLogo()
{
	// 無し
}
//================================
// 生成処理
//================================
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nAnchorType)
{
	// インスタンス生成
	CTitleLogo* pTitlelogo = new CTitleLogo;

	// nullだった場合
	if (pTitlelogo == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTitlelogo->Init()))
	{
		return nullptr;
	}

	// 2Dオブジェクト設定
	pTitlelogo->SetPos(pos);
	pTitlelogo->SetSize(fWidth, fHeight);
	pTitlelogo->SetAnchor(nAnchorType);
	pTitlelogo->SetTexture();

	// 生成されたポインタを返す
	return pTitlelogo;
}
//================================
// 初期化処理
//================================
HRESULT CTitleLogo::Init(void)
{
	// 親クラスの初期化
	CObject2D::Init();

	// 初期化結果を返す
	return S_OK;
}
//================================
// 終了処理
//================================
void CTitleLogo::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//================================
// 更新処理
//================================
void CTitleLogo::Update(void)
{
	// 親クラスの更新処理
	CObject2D::Update();
}
//================================
// 描画処理
//================================
void CTitleLogo::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullチェック
	if (pTexture == nullptr) return;

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// 親クラスの描画処理
	CObject2D::Draw();
}
//================================
// テクスチャ割り当て処理
//================================
void CTitleLogo::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullチェック
	if (pTexture == nullptr) return;

	// テクスチャ割り当て
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\logo.png");
}
