//=====================================
//
// 選択ポイントUI処理 [ pointui.h ]
// Author: Asuma Nishio
//
//=====================================

//*****************************
// インクルードファイル
//*****************************
#include "pointui.h"
#include "manager.h"
#include "texture.h"

//*****************************
// 名前空間
//*****************************
namespace POINTINFO
{
	constexpr float POINTWIDTH = 30.0f;	// 横幅
	constexpr float POINTHEIGHT = 40.0f;// 高さ
};

//==============================
// オーバーロードコンストラクタ
//==============================
CPointUi::CPointUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nIdxTex = NULL;
}
//==============================
// デストラクタ
//==============================
CPointUi::~CPointUi()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CPointUi* CPointUi::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CPointUi* pPoint = new CPointUi;
	if (pPoint == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pPoint->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pPoint->SetPos(pos);
	pPoint->SetSize(POINTINFO::POINTWIDTH, POINTINFO::POINTHEIGHT);
	pPoint->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pPoint->SetTexture();

	// 生成されたポインタを返す
	return pPoint;
}
//==============================
// 初期化処理
//==============================
HRESULT CPointUi::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// 初期化結果
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CPointUi::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//==============================
// 更新処理
//==============================
void CPointUi::Update(void)
{
	// 親クラスの更新処理
	CObject2D::Update();
}
//==============================
// 描画処理
//==============================
void CPointUi::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullだったらここで処理終了
	if (pTexture == nullptr) return;

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// 親クラスの描画処理
	CObject2D::Draw();
}
//==============================
// テクスチャ割り当て処理
//==============================
void CPointUi::SetTexture(void)
{
	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullだったらここで処理終了
	if (pTexture == nullptr) return;

	// 割り当て
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\PointUi.png");
}
