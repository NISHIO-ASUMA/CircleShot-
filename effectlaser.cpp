//============================================
//
// レーザーエフェクト処理 [ effectlaser.cpp ]
// Author: Asuma Nishio
//
//============================================

//**********************
// インクルードファイル
//**********************
#include "effectlaser.h"
#include "manager.h"
#include "texture.h"

//====================================
// オーバーロードコンストラクタ
//====================================
CEffectLaser::CEffectLaser(int nPriority) : CBillboard(nPriority)
{
	m_nIdxTex = NULL;
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
}
//====================================
// デストラクタ
//====================================
CEffectLaser::~CEffectLaser()
{
	// 無し
}
//====================================
// 生成処理
//====================================
CEffectLaser* CEffectLaser::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// インスタンス生成
	CEffectLaser* pLaser = new CEffectLaser;

	// nullなら
	if (pLaser == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pLaser->Init()))
	{
		return nullptr;
	}

	// オブジェクトセット
	pLaser->SetTexture();
	pLaser->SetPos(pos);
	pLaser->SetSize(fRadius, fRadius);
	pLaser->SetCol(col);

	// TODO : メンバポインタに代入
	
	// 生成されたポインタを返す
	return pLaser;
}
//====================================
// 初期化処理
//====================================
HRESULT CEffectLaser::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();

	// 初期化結果を返す
	return S_OK;
}
//====================================
// 終了処理
//====================================
void CEffectLaser::Uninit(void)
{
	// 親クラスの終了
	CBillboard::Uninit();
}
//====================================
// 更新処理
//====================================
void CEffectLaser::Update(void)
{
	// 親クラスの更新処理
	CBillboard::Update();
}
//====================================
// 描画処理
//====================================
void CEffectLaser::Draw(void)
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
//====================================
// テクスチャ割り当て処理
//====================================
void CEffectLaser::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullなら
	if (pTexture == nullptr) return;

	// テクスチャ割り当て
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\effect000.jpg");
}