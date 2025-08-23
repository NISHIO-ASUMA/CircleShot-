//============================================
//
// シールド耐久値関数 [ barrierdurability.cpp ]
// Author : Asuma Nishio
// 
// TODO : こっちは描画を管理するだけ!
//
//============================================

//*********************************
// インクルードファイル
//*********************************
#include "barrierdurability.h"
#include "manager.h"
#include "texture.h"

//=======================================
// オーバーロードコンストラクタ
//=======================================
CBarrierDurability::CBarrierDurability(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_isCreate = false;
	m_nIdxTex = NULL;
	m_nDurability = NULL;
}
//=======================================
// デストラクタ
//=======================================
CBarrierDurability::~CBarrierDurability()
{
	// 無し
}
//=======================================
// 生成処理
//=======================================
CBarrierDurability* CBarrierDurability::Create(D3DXVECTOR3 pos, D3DXCOLOR col,float fHeight, float fWidth, int nType)
{
	// インスタンス性生成
	CBarrierDurability* pbarrier = new CBarrierDurability;

	// nullなら
	if (pbarrier == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pbarrier->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pbarrier->SetPos(pos);
	pbarrier->SetSize(fWidth, fHeight);
	pbarrier->SetCol(col);
	pbarrier->SetTexture(nType);
	pbarrier->SetAnchor(ANCHORTYPE_CENTER);

	// 生成されたポインタを返す
	return pbarrier;
}
//=======================================
// 初期化処理
//=======================================
HRESULT CBarrierDurability::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// オブジェクトの種類定義
	SetObjType(TYPE_BARRIER);

	// 初期化結果を返す
	return S_OK;
}
//=======================================
// 終了処理
//=======================================
void CBarrierDurability::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//=======================================
// 更新処理
//=======================================
void CBarrierDurability::Update(void)
{
	// 親クラスの更新処理
	CObject2D::Update();
}
//=======================================
// 描画処理
//=======================================
void CBarrierDurability::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// nullなら
	if (pDevice == nullptr) return;

	// マネージャーからポインタ取得
	CTexture* pTex = CManager::GetTexture();

	// nullなら
	if (pTex == nullptr) return;

	// テクスチャをセットする
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdxTex));

	// 親クラスの描画
	CObject2D::Draw();
}
//=======================================
// テクスチャ割り当て処理
//=======================================
void CBarrierDurability::SetTexture(int nType)
{
	// マネージャーからポインタ取得
	CTexture* pTex = CManager::GetTexture();

	// nullなら
	if (pTex == nullptr) return;

	// 各種類分け
	switch (nType)
	{
	case CBarrierDurability::GUARD_FRAME: // 枠
		// m_nIdxTex = pTex->Register();

		break;

	case CBarrierDurability::GUARD_FIRST: // 3分の1
		// m_nIdxTex = pTex->Register();

		break;

	case CBarrierDurability::GUARD_SECOND: // 3分の2
		// m_nIdxTex = pTex->Register();

		break;

	case CBarrierDurability::GUARD_THIRD: // 最大値
		// m_nIdxTex = pTex->Register();

		break;

	default:
		m_nIdxTex = -1;
		break;
	}
}
