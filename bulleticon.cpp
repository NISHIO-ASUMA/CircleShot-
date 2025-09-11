//========================================
//
// 弾アイコン処理 [ bulleticon.cpp ]
// Author: Asuma Nishio
//
//========================================

//***************************
// インクルードファイル宣言
//***************************
#include "bulleticon.h"
#include "manager.h"
#include "texture.h"
#include "bullet.h"

//***************************
// 名前空間
//***************************
namespace BULLETICONINFO
{
	constexpr float ICONSIZE = 30.0f;	// サイズ
};

//==================================
// オーバーロードコンストラクタ
//==================================
CBulletIcon::CBulletIcon(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nIdxTex = NULL;
	m_nIdx = NULL;
}
//==================================
// デストラクタ
//==================================
CBulletIcon::~CBulletIcon()
{
	// 無し
}
//==================================
// 生成処理
//==================================
CBulletIcon* CBulletIcon::Create(D3DXVECTOR3 pos, const char* pTexName,int nIdx)
{
	// インスタンス生成
	CBulletIcon* pIcon = new CBulletIcon;
	if (pIcon == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pIcon->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pIcon->SetPos(pos);
	pIcon->SetSize(BULLETICONINFO::ICONSIZE, BULLETICONINFO::ICONSIZE);
	pIcon->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pIcon->SetTexture(pTexName);
	pIcon->m_nIdx = nIdx;

	// 生成されたポインタを返す
	return pIcon;
}
//==================================
// 初期化処理
//==================================
HRESULT CBulletIcon::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	return S_OK;
}
//==================================
// 終了処理
//==================================
void CBulletIcon::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//==================================
// 更新処理
//==================================
void CBulletIcon::Update(void)
{
	// 弾の種類を取得
	int nType = static_cast<int>(CBullet::GetType());

	// 一致していたら
	if (m_nIdx == nType)
	{
		// カラー変更
		SetCol(COLOR_WHITE);
	}
	else
	{
		// カラー変更
		SetCol(COLOR_GLAY);
	}

	// 親クラスの更新処理
	CObject2D::Update();
}
//==================================
// 描画処理
//==================================
void CBulletIcon::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullチェック
	if (pTexture == nullptr) return;

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// オブジェクト描画
	CObject2D::Draw();
}
//==================================
// テクスチャ処理
//==================================
void CBulletIcon::SetTexture(const char* pTexName)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullチェック
	if (pTexture == nullptr) return;

	// パスを設定
	m_nIdxTex = pTexture->Register(pTexName);
}
