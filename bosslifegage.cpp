//=========================================
//
// ボス体力処理 [ bosslifegage.h ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// インクルードファイル
//**********************
#include "bosslifegage.h"
#include "manager.h"
#include "gamemanager.h"
#include "parameter.h"
#include "object2D.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CBossLifeGage::CBossLifeGage(int nPriority) : CGage(nPriority)
{
	// 値のクリア
	m_nIdxTex = NULL;
	m_pBoss = nullptr;

	m_nCurrentLifeLength = NULL;
	m_nMaxLifeLength = NULL;
	m_Type = TYPE_FRAME;
}
//===============================
// デストラクタ
//===============================
CBossLifeGage::~CBossLifeGage()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CBossLifeGage* CBossLifeGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	// インスタンス生成
	CBossLifeGage* pBossLife = new CBossLifeGage;

	// nullだったら
	if (pBossLife == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pBossLife->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pBossLife->SetPos(pos);
	pBossLife->SetSize(fWidth, fHeight);
	pBossLife->SetType(nType);
	pBossLife->SetTexture(nType);
	pBossLife->SetAnchor(CObject2D::ANCHORTYPE_LEFTSIDE);

	// 生成されたポインタを返す
	return pBossLife;
}
//===============================
// 初期化処理
//===============================
HRESULT CBossLifeGage::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// ボスの取得
	if (m_pBoss == nullptr)
	{
		// プレイヤー取得
		m_pBoss = CGameManager::GetBoss();
	}

	// 取得できたら
	if (m_pBoss != nullptr)
	{
		// パラメーター取得
		CParameter* pParam = m_pBoss->GetParam();

		// 最大値体力を設定する
		m_nMaxLifeLength = pParam->GetHp();
	}

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CBossLifeGage::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//===============================
// 更新処理
//===============================
void CBossLifeGage::Update(void)
{
	// 死亡していたら
	if (m_pBoss->IsDaeth()) return;

	// nullじゃない かつ 種類がバーの時
	if (m_pBoss != nullptr && m_Type == TYPE_GAGE)
	{
		// パラメーター取得
		CParameter* pParam = m_pBoss->GetParam();

		// 現在の体力を取得
		m_nCurrentLifeLength = pParam->GetHp();

		// ゲージの長さ設定
		SetGageLength(m_nMaxLifeLength, m_nCurrentLifeLength, 0.4f, 60.0f);
	}

	// 親クラスの更新処理
	CObject2D::Update();
}
//===============================
// 描画処理
//===============================
void CBossLifeGage::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ読み込み
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// 親クラスの描画
	CObject2D::Draw();
}
//===============================
// テクスチャ割り当て処理
//===============================
void CBossLifeGage::SetTexture(int nType)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	switch (nType)
	{
	case CBossLifeGage::TYPE_FRAME:	// 外枠

		// テクスチャ割り当て
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\boss_frame.png");
		break;

	case CBossLifeGage::TYPE_GAGE:	// 体力バー

		// テクスチャ割り当て
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\boss_life.png");
		break;

	default:
		m_nIdxTex = -1;
		break;
	}
}
