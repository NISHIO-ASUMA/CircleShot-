//====================================
//
// 影処理 [ shadow.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "shadow.h"
#include "manager.h"

//**********************
// 定数宣言
//**********************
constexpr float SHADOW_SIZE = 40.0f; // 影の大きさ

//=================================
// オーバーロードコンストラクタ
//=================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	// 値のクリア
	m_nTexIdx = NULL;
}
//=================================
// デストラクタ
//=================================
CShadow::~CShadow()
{
	// 無し
}
//==================================
// 生成処理
//==================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンス生成
	CShadow* pShadow = new CShadow;

	// nullptrだったら
	if (pShadow == nullptr) return nullptr;

	// オブジェクト設定
	pShadow->SetPos(pos);
	pShadow->SetRot(rot);
	pShadow->SetSize(SHADOW_SIZE, SHADOW_SIZE);
	pShadow->SetTexture();

	// 初期化失敗時
	if (FAILED(pShadow->Init()))
	{
		// 処理を返す
		return nullptr;
	}

	// 影のポインタを返す
	return pShadow;
}
//=================================
// 影の初期化処理
//=================================
HRESULT CShadow::Init(void)
{
	// 親クラスの初期化
	CObject3D::Init();

	return S_OK;
}
//=================================
// 影の終了処理
//=================================
void CShadow::Uninit(void)
{
	// 影の終了処理
	CObject3D::Uninit();
}
//=================================
// 影の更新処理
//=================================
void CShadow::Update(void)
{
	// 無し
}
//=================================
// 影の描画処理
//=================================
void CShadow::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// 減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// 親クラスの描画
	CObject3D::Draw();

	// 減算合成を戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=================================
// テクスチャ設定処理
//=================================
void CShadow::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャクラスに登録
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\shadow000.jpg");
}
//=================================
// 影座標更新処理
//=================================
void CShadow::UpdatePos(D3DXVECTOR3 pos)
{
	// 座標セット
	SetPos(pos);
}
