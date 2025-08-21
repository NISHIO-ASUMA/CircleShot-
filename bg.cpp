//====================================
//
// 背景処理 [ bg.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "bg.h"
#include "manager.h"
#include "object.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_ScrollSpeed = 0.0f;
	m_IndexBg = 0;
	m_nIdxTexture = 0;
}
//===============================
// デストラクタ
//===============================
CBg::~CBg()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CBg* CBg::Create(int nIdxBg)
{
	// 背景のポインタ宣言
	CBg* pBg;

	// インスタンス生成
	pBg = new CBg;

	// 番号を代入
	pBg->m_IndexBg = nIdxBg;

	// テクスチャセット
	pBg->SetTexture(nIdxBg);

	// スクロール速度をレイヤーごとに設定
	switch (nIdxBg)
	{
	case BG_BACK: 
		pBg->SetScrollSpeed(0.003f); 
		break; // 奥

	case BG_CENTER: 
		pBg->SetScrollSpeed(0.006f);
		break; // 真ん中

	case BG_FRONT:
		pBg->SetScrollSpeed(0.009f); 
		break; // 手前

	default:
		break;
	}

	// 初期化処理
	if (FAILED(pBg->Init()))
	{
		// 破棄
		delete pBg;

		// NULLにする
		return nullptr;
	}

	// 2D描画設定
	pBg->SetRot(D3DXVECTOR3(VECTOR3_NULL));
	pBg->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// 背景のポインタを返す
	return pBg;
}
//===============================
// 背景の初期化処理
//===============================
HRESULT CBg::Init(void)
{
	// 親クラスの初期化
	CObject2D::Init();

	// 結果を返す
	return S_OK;
}
//===============================
// 背景の終了処理
//===============================
void CBg::Uninit(void)
{
	// 2Dオブジェクトの破棄
	CObject2D::Uninit();
}
//===============================
// 背景の更新処理
//===============================
void CBg::Update(void)
{
	// テクスチャのスクロールを代入
	m_TexScroll.x += m_ScrollSpeed;

	// テクスチャ座標の更新関数
	// SetUV(m_TexScroll.x, 1.0f + m_TexScroll.x, 1.0f);
}
//===============================
// 背景の描画処理
//===============================
void CBg::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 2Dオブジェクトの描画
	CObject2D::Draw();
}
//===============================
// テクスチャセット関数
//===============================
void CBg::SetTexture(int nType)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	switch (nType)
	{
	case BG_BACK:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\field000.jpeg");
		break;
	case BG_CENTER:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\field000.jpeg");
		break;

	case BG_FRONT:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\field000.jpeg");
		break;

	default:
		break;
	}
}
