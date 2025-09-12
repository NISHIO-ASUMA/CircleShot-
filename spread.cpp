//=====================================
//
// 拡散オブジェクト処理 [ spread.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "spread.h"

//**********************
// 名前空間
//**********************
namespace SPREADINFO
{
	constexpr float GRAVITY = 0.5f;	// 重力値
	constexpr float FIRSTBOUNCE = 12.0f; // 一回目のバウンド
	constexpr float SECONDBOUNCE = 3.0f; // 二回目のバウンド
};

//=================================
// オーバーロードコンストラクタ
//=================================
CSpread::CSpread(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_fUpSpeed = NULL;
	m_nBounceCount = NULL;
}
//=================================
// デストラクタ
//=================================
CSpread::~CSpread()
{
	// 無し
}
//=================================
// 生成処理
//=================================
CSpread* CSpread::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンス生成
	CSpread* pSpread = new CSpread;
	if (pSpread == nullptr) return nullptr;

	// オブジェクト設定
	pSpread->SetFilePass("data\\MODEL\\STAGEOBJ\\Spread.x");
	pSpread->SetPos(pos);
	pSpread->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pSpread->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pSpread;
}
//=================================
// 初期化処理
//=================================
HRESULT CSpread::Init(void)
{
	// 親クラスの初期化処理
	CObjectX::Init();

	return S_OK;
}
//=================================
// 終了処理
//=================================
void CSpread::Uninit(void)
{
	// 親クラスの終了処理
	CObjectX::Uninit();
}
//=================================
// 更新処理
//=================================
void CSpread::Update(void)
{
	// 現在座標を取得
	D3DXVECTOR3 pos = GetPos();

	// 重力を加える
	m_fUpSpeed -= SPREADINFO::GRAVITY;
	pos.y += m_fUpSpeed;

	// 地面に到達
	if (pos.y <= 0.0f)
	{
		// 座標を設定
		pos.y = 0.0f;

		// カウントを加算
		m_nBounceCount++;

		switch (m_nBounceCount)
		{
		case 1:
			// 1回目のバウンド
			m_fUpSpeed = SPREADINFO::FIRSTBOUNCE;	// 高めに設定
			break;

		case 2:
			// 2回目のバウンド
			m_fUpSpeed = SPREADINFO::SECONDBOUNCE;	// 小さめに設定
			break;

		case 3:
			// 3回目終了
			Uninit();

			return;

		default:
			break;
		}
	}

	// 座標にセット
	SetPos(pos);

	// 親クラスの更新処理
	CObjectX::Update();
}
//=================================
// 描画処理
//=================================
void CSpread::Draw(void)
{
	// 親クラスの描画処理
	CObjectX::Draw();
}