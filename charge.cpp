//========================================
//
// チャージ処理 [ charge.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// インクルードファイル
//**********************************
#include "charge.h"
#include "manager.h"
#include "texture.h"

//**********************************
// 名前空間
//**********************************
namespace CHARGEINFO
{
	constexpr float MAX_CHARGE = 100.0f;	// 最大チャージ数
};

//**********************************
// 静的メンバ変数宣言
//**********************************
float CCharge::m_fCharge = NULL;

//================================
// コンストラクタ
//================================
CCharge::CCharge(int nPriority) : CGage(nPriority)
{
	// 値のクリア
	m_nIdxTex = NULL;
	m_nType = NULL;
}
//================================
// デストラクタ
//================================
CCharge::~CCharge()
{
	// 無し
}
//================================
// 生成処理
//================================
CCharge* CCharge::Create(D3DXVECTOR3 pos,float fWidth, float fHeight, int nType)
{
	// インスタンス生成
	CCharge* pCharge = new CCharge;

	// nullなら
	if (pCharge == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pCharge->Init()))
	{
		return nullptr;
	}

	// 2Dオブジェクト設定
	pCharge->SetPos(pos);
	pCharge->SetSize(fWidth, fHeight);
	pCharge->SetType(nType);
	pCharge->SetTexture(nType);
	pCharge->SetAnchor(ANCHORTYPE_LEFTSIDE);

	// 生成されたポインタを返す
	return pCharge;
}
//================================
// 加算処理
//================================
void CCharge::AddCharge(float fValue)
{
	m_fCharge += fValue;

	if (m_fCharge >= CHARGEINFO::MAX_CHARGE)
	{
		m_fCharge = CHARGEINFO::MAX_CHARGE;
	}
}
//================================
// 減算処理
//================================
void CCharge::DecCharge(float fValue)
{
	m_fCharge -= fValue;

	if (m_fCharge <= 0.0f)
	{
		m_fCharge = 0.0f;
	}
}
//================================
// 初期化処理
//================================
HRESULT CCharge::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// 初期化結果を返す
	return S_OK;
}
//================================
// 終了処理
//================================
void CCharge::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//================================
// 更新処理
//================================
void CCharge::Update(void)
{
	// 種類がバーの時
	if (m_nType == CHARGE_BAR)
	{
		// ゲージの長さ設定
		FSetGageLength(CHARGEINFO::MAX_CHARGE, m_fCharge, 305.0f, 38.0f);
	}

	// 親クラスの更新処理
	CObject2D::Update();
}
//================================
// 描画処理
//================================
void CCharge::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ読み込み
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// 親クラスの描画処理
	CObject2D::Draw();
}
//================================
// テクスチャ割り当て処理
//================================
void CCharge::SetTexture(int nType)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// もしnullなら
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case CHARGE_FRAME:	// 枠
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\laser.png");
		break;

	case CHARGE_BAR:	// 本体
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\laser_gage.png");
		break;

	default:
		m_nIdxTex = -1;	// 例外の値
		break;
	}
}