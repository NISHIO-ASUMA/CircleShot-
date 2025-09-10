//====================================
//
// UI処理 [ ui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "ui.h"
#include "texture.h"
#include "manager.h"
#include "easing.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CUi::CUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nTexIdxType = NULL;
	m_isFlash = false;
	m_nFlashFrame = NULL;
	m_nState = STATE_NONE;
}
//===============================
// デストラクタ
//===============================
CUi::~CUi()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CUi::Init(void)
{
	// オブジェクトの初期化
	CObject2D::Init();

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CUi::Uninit(void)
{
	// オブジェクトの終了
	CObject2D::Uninit();
}
//===============================
// 更新処理
//===============================
void CUi::Update(void)
{
	// 点滅有効時
	if (m_isFlash)
	{
		// 点滅処理
		SetFlash(NULL, m_nFlashFrame, COLOR_WHITE);
	}

	if (m_nState == STATE_FALL && !m_isFlash)
	{
		// 現在座標を取得
		D3DXVECTOR3 NowPos = GetPos();
		
		// 下に移動
		NowPos.y += 10.0f;

		// 座標セット
		SetPos(NowPos);

		if (NowPos.y >= SCREEN_HEIGHT + 50.0f)
		{
			// 終了処理
			Uninit();

			// 下の処理に入らないようにする
			return;
		}
	}

	// 親クラス更新
	CObject2D::Update();
}
//===============================
// 描画処理
//===============================
void CUi::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャセット
	CTexture* pTexture = CManager::GetTexture();

	// 割り当て
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdxType));

	// オブジェクトの描画
	CObject2D::Draw();
}
//===============================
// 生成処理
//===============================
CUi* CUi::Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight, const char* Filename, bool isUse)
{
	// インスタンス生成
	CUi* pUi = new CUi;

	// nullなら
	if (pUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pUi->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// オブジェクト設定
	pUi->SetPos(pos);
	pUi->SetSize(fWidth, fHeight);
	pUi->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pUi->SetTexture(Filename);
	pUi->m_nFlashFrame = nFlashFrame;
	pUi->m_isFlash = isUse;

	// 生成されたポインタを返す
	return pUi;
}
//===============================
// テクスチャセット処理
//===============================
void CUi::SetTexture(const char* pRegistername)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullじゃなかったら
	if (pTexture != nullptr)
	{
		// テクスチャ設定
		m_nTexIdxType = pTexture->Register(pRegistername);
	}
}