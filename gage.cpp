//============================================
//
// ゲージ関係のクラス処理 [ gage.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードファイル
//**********************
#include "gage.h"
#include "texture.h"
#include "manager.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CGage::CGage(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
}
//===============================
// デストラクタ
//===============================
CGage::~CGage()
{
	// 無し
}
//===============================
// 初期化処理
//===============================
HRESULT CGage::Init(void)
{
	// 親クラスの初期化
	CObject2D::Init();

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CGage::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//===============================
// 更新処理
//===============================
void CGage::Update(void)
{
	// 親クラスの更新
	CObject2D::Update();
}
//===============================
// 描画処理
//===============================
void CGage::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ読み込み
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTextIdx));

	// 親クラスの描画
	CObject2D::Draw();
}
//===============================
// 描画処理
//===============================
CGage* CGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// インスタンス生成
	CGage* pGage = new CGage;

	// 生成できなかったら
	if (pGage == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pGage->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// 2Dオブジェクト設定
	pGage->SetPos(pos);
	pGage->SetSize(fWidth, fHeight);

	// ポインタを返す
	return pGage;
}
//===============================
// ゲージの長さ設定処理
//===============================
void CGage::SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue,float Height)
{
	// 最大比率を出す
	float fRatio = 1.0f;

	// 0以上なら
	if (nMaxLife > NULL)
	{
		// 割合を計算する
		fRatio = static_cast<float>(nCurrentLife) / static_cast<float>(nMaxLife);
	}

	// 表示する体力バーの最大幅
	const float fMaxWidth = SCREEN_WIDTH * fValue;

	// サイズを比率で反映
	SetSize(fMaxWidth * fRatio, Height);
}
