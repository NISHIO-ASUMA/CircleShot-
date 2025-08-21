//====================================
//
// リザルトui処理処理 [ resultui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "resultui.h"
#include "texture.h"
#include "manager.h"

//============================
// コンストラクタ
//============================
CResultUi::CResultUi(int nPriority) : CObject2D(nPriority)
{
    // 値のクリア
    m_nIdxTex = NULL;
}
//============================
// デストラクタ
//============================
CResultUi::~CResultUi()
{
    // 無し
}
//============================
// 初期化処理
//============================
HRESULT CResultUi::Init(void)
{
	// 2Dオブジェクトの初期化処理
	CObject2D::Init();

	// 頂点タイプを設定
	SetAnchor(ANCHORTYPE_CENTER);

	// 初期化結果を返す
	return S_OK;
}
//============================
// 終了処理
//============================
void CResultUi::Uninit(void)
{
	// 2Dオブジェクトの終了処理
	CObject2D::Uninit();
}
//============================
// 更新処理
//============================
void CResultUi::Update(void)
{
	// 2Dオブジェクトの更新処理
	CObject2D::Update();
}
//============================
// 描画処理
//============================
void CResultUi::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullだったらここで処理終了
	if (pTexture == nullptr) return;

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// 2Dオブジェクトの描画処理
	CObject2D::Draw();
}
//============================
// 生成処理
//============================
CResultUi* CResultUi::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType)
{
	// インスタンス生成
	 CResultUi* pResultUi = new CResultUi;

	 // nullチェック
	 if (pResultUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pResultUi->Init()))
	{
		// nullを返す
		return nullptr;
	}

	// 2Dオブジェクト設定
	pResultUi->SetPos(pos);
	pResultUi->SetCol(col);
	pResultUi->SetSize(fWidth, fHeight);
	pResultUi->SetTexture(nType);

	// 生成されたポインタを返す
	return pResultUi;
}
//============================
// テクスチャ割り当て
//============================
void CResultUi::SetTexture(int nType)
{
	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullだったらここで処理終了
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case CResultUi::TYPE_NONE:
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\resultlogo.png");
		break;

	default:
		m_nIdxTex = -1;
		break;
	}
}
