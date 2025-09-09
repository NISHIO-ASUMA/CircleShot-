//==========================================
//
// 柱状エフェクト処理 [ effectpiler.cpp ]
// Author: Asuma Nishio
//
// 
// TODO : 柱状のエフェクト作成
// 
//==========================================

//***************************
// インクルードファイル宣言
//***************************
#include "effectpiler.h"
#include "manager.h"
#include "template.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CEffectPiler::CEffectPiler(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_nLife = NULL;
	m_fRadius = NULL;
	m_nIdxTex = NULL;
}
//===============================
// デストラクタ
//===============================
CEffectPiler::~CEffectPiler()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CEffectPiler* CEffectPiler::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife)
{
	// インスタンス生成
	CEffectPiler* pEffect = new CEffectPiler;
	if (pEffect == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pEffect->SetPos(pos);
	pEffect->SetRot(rot);
	pEffect->SetSize(fRadius, fRadius);
	pEffect->SetCol(LASER);
	pEffect->SetTexture();

	pEffect->m_nLife = nLife;
	pEffect->m_fRadius = fRadius;

	// 生成されたポインタを返す
	return pEffect;
}
//===============================
// 初期化処理
//===============================
HRESULT CEffectPiler::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CEffectPiler::Uninit(void)
{
	// 親クラスの終了処理
	CBillboard::Uninit();
}
//===============================
// 更新処理
//===============================
void CEffectPiler::Update(void)
{
	// 寿命を減らす
	m_nLife--;

	float fWidth = GetWidth();
	float fHeight = GetHeight();

	float maxHeight = 180.0f;	// 光柱の最大高さ

	// 縦方向に伸ばす
	float growSpeed = 5.0f;	// 縦に伸びるスピード

	if (fHeight < maxHeight)
	{
		fHeight += growSpeed;

		D3DXVECTOR3 pos = GetPos();
		pos.y += growSpeed;
		SetPos(pos);
	}

	// 大きさの更新
	SetSize(fWidth, fHeight);

	// 寿命切れで削除
	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();

		// 処理終了
		return;
	}

	// 親クラスの更新処理
	CBillboard::Update();
}
//===============================
// 描画処理
//===============================
void CEffectPiler::Draw(void)
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

	//　親クラス描画
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
void CEffectPiler::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullなら
	if (pTexture == nullptr) return;

	// テクスチャ割り当て
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\effect000.jpg");
}