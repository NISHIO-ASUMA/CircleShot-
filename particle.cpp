//====================================
//
// パーティクル処理 [ particle.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "particle.h"
#include "manager.h"
#include "effect.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nMaxParticle = NULL;
	m_nLife = NULL;
	m_nLength = NULL;
	m_nRadius = NULL;
}
//===============================
// デストラクタ
//===============================
CParticle::~CParticle()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle,int nRadius,int nLength,int nLife)
{
	// パーティクルのポインタを宣言
	CParticle* pParticle = new CParticle;

	// nullだったら
	if (pParticle == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pParticle->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// オブジェクト設定
	pParticle->m_pos = pos;
	pParticle->m_col = col;
	pParticle->m_nMaxParticle = nMaxParticle;
	pParticle->m_nLength = nLength;
	pParticle->m_nLife = nLife;
	pParticle->m_nRadius = nRadius;

	// ポインタを返す
	return pParticle;
}
//===============================
// 初期化処理
//===============================
HRESULT CParticle::Init(void)
{
	// 配列クリア
	m_pEffect.clear();

	//乱数の種を宣言(1つのみの宣言)
	srand((unsigned int)time(NULL));

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CParticle::Uninit(void)
{
	// 配列クリア
	m_pEffect.clear();

	// 親クラスの破棄
	CObject::Release();
}
//===============================
// 更新処理
//===============================
void CParticle::Update(void)
{
	//カラーの設定
	D3DXCOLOR col = m_col;

	// 座標を取得
	D3DXVECTOR3 pos = m_pos;

	//パーティクルの生成
	for (int nCntApper = 0; nCntApper < m_nMaxParticle; nCntApper++)
	{
		// 移動量の設定
		float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
		float fAngelY = (float)(rand() % 629 - 314) / 100.0f;

		// 長さ設定
		float fLength = ((float)(rand() % m_nLength) / 10.0f);

		// 移動量変数
		D3DXVECTOR3 Move = VECTOR3_NULL;

		// 移動距離設定
		Move.x = sinf(fAngelX) * sinf(fAngelY) * fLength;
		Move.y = cosf(fAngelX) * fLength;
		Move.z = sinf(fAngelX) * cosf(fAngelY) * fLength;

		//半径の設定
		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.7f);

		// 寿命の設定
		int nLife = ((float)(rand() % m_nLife) / 10);

		// エフェクト生成
		CEffect* pEffect = CEffect::Create(pos, col, Move, nLife, fRadius);

		if (pEffect)
		{
			// 配列に追加
			m_pEffect.push_back(pEffect);
		}
		else
		{
			break;
		}
	}

	// 破棄
	Uninit();
}
//=========================
// 描画処理
//==========================
void CParticle::Draw(void)
{
	// 無し
}
