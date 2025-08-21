//=====================================
//
// 攻撃前兆演出 [ attacksign.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "attacksign.h"
#include "manager.h"
#include "texture.h"

//**********************
// 名前空間
//**********************
namespace ATTACKSIGN
{
	inline constexpr int LIFE = 60; // 最大寿命
	const D3DXVECTOR3 SIGNPOS = { 640.0f,60.0f,0.0f }; // UI座標
};

//==============================
// コンストラクタ
//==============================
CAttackSign::CAttackSign(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nidxTex = NULL;
	m_nLife = NULL;
}
//==============================
// デストラクタ
//==============================
CAttackSign::~CAttackSign()
{
	// 無し
}
//==============================
// 初期化処理
//==============================
HRESULT CAttackSign::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// 寿命を設定
	m_nLife = ATTACKSIGN::LIFE;
	
	// 初期化結果を返す
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CAttackSign::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//==============================
// 更新処理
//==============================
void CAttackSign::Update(void)
{
	// 点滅処理を実行
	SetFlash(2, 5);

	// 体力を減らす
	m_nLife--;

	// 0以下
	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();

		// ここで処理終了
		return;
	}

	// オブジェクト更新
	CObject2D::Update();
}
//==============================
// 描画処理
//==============================
void CAttackSign::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullチェック
	if (pTexture == nullptr) return;

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nidxTex));

	// オブジェクト描画
	CObject2D::Draw();
}
//==============================
// テクスチャ割り当て
//==============================
void CAttackSign::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullチェック
	if (pTexture == nullptr) return;

	// パスを設定
	m_nidxTex = pTexture->Register("data\\TEXTURE\\alert.png");
}
//==============================
// 生成処理
//==============================
CAttackSign* CAttackSign::Create(float fWidth, float fHeight)
{
	// インスタンス生成
	CAttackSign* pAttack = new CAttackSign;

	// nullチェック
	if (pAttack == nullptr) return nullptr;

	// オブジェクト設定
	pAttack->SetPos(ATTACKSIGN::SIGNPOS);
	pAttack->SetSize(fWidth, fHeight);
	pAttack->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pAttack->SetTexture();

	// 初期化失敗時
	if (FAILED(pAttack->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pAttack;
}