//====================================
//
// 爆発処理 [ explosion.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "explosion.h"
#include "manager.h"

//***********************************
// マクロ定義
//***********************************
#define NUM_PATTERN (8)
#define NUM_ANIM (2)
#define TEX_U (0.125f)
#define TEX_V (1.0f)
#define EXPLOSION_SIZE_X (100.0f)
#define EXPLOSION_SIZE_Y (100.0f)

//===============================
// オーバーロードコンストラクタ
//===============================
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nIdxTexture = NULL;
}
//===============================
// デストラクタ
//===============================
CExplosion::~CExplosion()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CExplosion* CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,D3DXCOLOR col)
{
	// 爆発のインスタンス生成
	CExplosion* pExplsion = new CExplosion;

	// テクスチャセット
	pExplsion->SetTexture();

	// 初期化に失敗したら
	if (FAILED(pExplsion->Init())) 
	{
		// 破棄
		delete pExplsion;

		// NULLを返す
		return nullptr;
	}

	// 2Dオブジェクト設定
	pExplsion->SetRot(rot);
	pExplsion->SetSize(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
	pExplsion->SetPos(pos);
	pExplsion->SetCol(col);

	return pExplsion;
}
//===============================
// 爆発の初期化処理
//===============================
HRESULT CExplosion::Init(void)
{
	// 親クラスの初期化
	CObject2D::Init();

	return S_OK;
}
//===============================
// 爆発の終了処理
//===============================
void CExplosion::Uninit(void)
{
	// オブジェクトの終了
	CObject2D::Uninit();
}
//===============================
// 爆発の更新処理
//===============================
void CExplosion::Update(void)
{
	// 現在の座標を取得
	D3DXVECTOR3 pos = GetPos();

	// 座標セット
	SetPos(pos);

	// アニメーションセット
	// SetAnim(NUM_PATTERN,NUM_ANIM, TEX_U, TEX_V);
}
//===============================
// 爆発の描画処理
//===============================
void CExplosion::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// オブジェクト描画
	CObject2D::Draw();
}
//===============================
// テクスチャセット
//===============================
void CExplosion::SetTexture()
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\explosion000.png");

}