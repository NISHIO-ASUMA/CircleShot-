//====================================
//
// エフェクト処理 [ effect.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "effect.h"
#include "manager.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CEffect::CEffect(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_nIdxTexture = NULL;
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
}
//===============================
// デストラクタ
//===============================
CEffect::~CEffect()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CEffect* CEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// エフェクトポインタ
	CEffect* pEffect = new CEffect;

	// nullptrだったら
	if (pEffect == nullptr) return nullptr;

	// テクスチャセット
	pEffect->SetTexture();

	// 初期化に失敗したら
	if (FAILED(pEffect->Init()))
	{
		// 破棄
		delete pEffect;

		// nullptrを代入
		pEffect = nullptr;
	}

	// 3Dオブジェクトセット
	pEffect->SetSize(fRadius, fRadius);
	pEffect->SetPos(pos);
	pEffect->SetCol(col);

	// 半径を代入
	pEffect->m_fRadius = fRadius;
	pEffect->m_move = move;
	pEffect->SetLife(nLife);

	// エフェクトポインタを返す
	return pEffect;
}
//===============================
// 初期化処理
//===============================
HRESULT CEffect::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CEffect::Uninit(void)
{
	// 親クラスの終了
	CBillboard::Uninit();
}
//===============================
// 更新処理
//===============================
void CEffect::Update(void)
{
	// 座標,カラー取得
	D3DXVECTOR3 Effectpos = GetPos();

	//カラーの設定
	D3DXCOLOR col = GetCol();

	// オブジェクト更新
	CBillboard::Update();

	// 移動量の更新
	Effectpos += m_move;

	// 半径をデクリメント
	m_fRadius -= 0.01f;

	// α値を減少
	col.a -= 0.005f;

	// 座標をセットする
	SetPos(Effectpos);

	// 色
	SetCol(col);

	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// サイズセット
	SetSize(m_fRadius, m_fRadius);

	// 体力を減らす
	m_nLife--;

	// 0以下の時
	if (m_nLife <= 0)
	{
		// 削除する
		Uninit();
	}
}
//===============================
// 描画処理
//===============================
void CEffect::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

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
//===============================
// テクスチャセット
//===============================
void CEffect::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャを登録する
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\effect000.jpg");
}
