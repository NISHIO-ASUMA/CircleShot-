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
#include "easing.h"

//================================
// オーバーロードコンストラクタ
//================================
CTitleLogo::CTitleLogo(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nTexIdx = NULL;
	m_move = VECTOR3_NULL;
	m_isAnimating = false;
	m_nFrame = NULL;
	m_nMaxFrame = NULL;
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
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
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
	pTitlelogo->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
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

	// 初期値を設定
	m_nMaxFrame = 800;

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
	// 入力チェック
	CInputKeyboard* pKey = CManager::GetInputKeyboard();

	if (pKey && pKey->GetTrigger(DIK_RETURN))
	{
		m_isAnimating = true;
		m_nFrame = 0;
	}

	if (m_isAnimating)
	{
		if (m_nFrame < m_nMaxFrame) m_nFrame++;

		CEasing ease;
		float t = ease.SetEase(m_nFrame, m_nMaxFrame);

		// EaseOutCubicを適用
		float e = ease.EaseOutCubic(t);

		// 開始位置・サイズ
		D3DXVECTOR3 startPos = GetPos();
		float startW = GetWidth(), startH = GetHeight();

		// 目的地・サイズ
		D3DXVECTOR3 destPos = { 200.0f, 80.0f, 0.0f };
		float destW = 180.0f, destH = 65.0f;

		// 補間
		D3DXVECTOR3 pos = startPos + (destPos - startPos) * e;
		float width = startW + (destW - startW) * e;
		float height = startH + (destH - startH) * e;

		// 完全到達したら静止
		if (m_nFrame >= m_nMaxFrame)
		{
			pos = destPos;
			width = destW;
			height = destH;
			m_isAnimating = false;  // アニメーション終了
		}

		// 値を反映
		SetPos(pos);
		SetSize(width, height);
	}

	// 親クラス更新
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
