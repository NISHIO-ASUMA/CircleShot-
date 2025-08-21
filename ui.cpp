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

//===============================
// オーバーロードコンストラクタ
//===============================
CUi::CUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nTexIdxType = NULL;
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
	//// 座標取得
	//D3DXVECTOR3 Pos = GetPos();

	//// 0.0fより小さい位置にいる
	//if (Pos.y <= 180.0f)
	//{
	//	Pos.y += 5.0f;
	//}

	//// 座標セット
	//SetPos(Pos);

	//if (m_type == UITYPE_NONE)
	//{
	//	SetFlash(10, 20);
	//}

	// オブジェクトの更新
	CObject2D::Update();
}
//===============================
// 描画処理
//===============================
void CUi::Draw(void)
{
	// カメラの取得
	CCamera* pCamera = CManager::GetCamera();

	// 取得失敗時
	if (pCamera == nullptr) return;

	// フラグをゲットする
	bool isKey = pCamera->GetIsRotation();

	if (!isKey)
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
	else
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
	
}
//===============================
// 生成処理
//===============================
CUi* CUi::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, const char* Filename, int nAnchorType)
{
	// インスタンス生成
	CUi* pUi = new CUi;

	// 初期化失敗時
	if (FAILED(pUi->Init()))
	{
		// ポインタの破棄
		delete pUi;

		// nullptr代入
		pUi = nullptr;

		// nullポインタを返す
		return nullptr;
	}

	// オブジェクト設定
	pUi->SetPos(pos);
	pUi->SetSize(fWidth, fHeight);
	pUi->SetAnchor(nAnchorType);
	pUi->SetTexture(Filename);

	// pUi->m_type = nType;

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
