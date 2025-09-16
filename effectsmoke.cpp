//==========================================
//
// 煙エフェクト処理 [ effectsmoke.h ]
// Author : Asuma Nishi
//
//==========================================

//**********************************
// インクルードファイル
//**********************************
#include "effectsmoke.h"
#include "manager.h"
#include "texture.h"

//=====================================
// オーバーロードコンストラクタ
//=====================================
CEffectSmoke::CEffectSmoke(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_nIdxTex = NULL;
	m_fRadius = NULL;
	m_nLife = NULL;
	m_move = VECTOR3_NULL;
}
//=====================================
// デストラクタ
//=====================================
CEffectSmoke::~CEffectSmoke()
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CEffectSmoke* CEffectSmoke::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// インスタンス生成
	CEffectSmoke* pEffect = new CEffectSmoke;

	// nullなら
	if (pEffect == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pEffect->SetSize(fRadius, 40.0f);
	pEffect->SetPos(pos);
	pEffect->SetCol(col);
	pEffect->m_fRadius = fRadius;
	pEffect->m_move = move;
	pEffect->m_nLife = nLife;

	// 生成したポインタを返す
	return pEffect;
}
//=====================================
// 初期化処理
//=====================================
HRESULT CEffectSmoke::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();

	// 初期化結果を返す
	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CEffectSmoke::Uninit(void)
{
	// 親クラスの終了処理
	CBillboard::Uninit();
}
//=====================================
// 更新処理
//=====================================
void CEffectSmoke::Update(void)
{
	// 寿命を減算
	m_nLife--;

	// 0以下なら
	if (m_nLife <= 0)
	{
		// 破棄
		Uninit();

		// 処理終了
		return;
	}

	// 親クラス更新処理
	CBillboard::Update();

	// テクスチャアニメーション
	SetAnim(8,1,0.25f, 1.0f);
}
//=====================================
// 描画処理
//=====================================
void CEffectSmoke::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// αブレンディングの加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテストを適用
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ビルボード描画
	CBillboard::Draw();

	// αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// αブレンディングを戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Zテストを戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
//=====================================
// テクスチャ割り当て処理
//=====================================
void CEffectSmoke::SetTexture(void)
{
	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();
	if (pTexture == nullptr) return;

	// 割り当て
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\explosion000.png");
}