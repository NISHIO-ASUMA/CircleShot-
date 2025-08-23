//=====================================================
//
// バリアオブジェクトの管理処理 [ barriermanager.cpp ]
// Author : Asuma Nishio
// 
// TODO : これをゲームマネージャーで取得できるようにしてポインタを渡す
//
//=====================================================

//*********************************
// インクルードファイル
//*********************************
#include "barriermanager.h"
#include "barrierdurability.h"

//*********************************
// 名前空間
//*********************************
namespace BARRIERINFO
{
	inline constexpr int MAX_GUARD = 3;
};

//============================
// コンストラクタ
//============================
CBarrierManager::CBarrierManager()
{
	// 値のクリア
	m_nBarrierNum = NULL;
	m_pBarrierUI = nullptr;
}
//============================
// デストラクタ
//============================
CBarrierManager::~CBarrierManager()
{
	// 無し
}
//============================
// 初期化処理
//============================
HRESULT CBarrierManager::Init(void)
{
	// 初期バリアUIを生成
	m_pBarrierUI = CBarrierDurability::Create
	(
		D3DXVECTOR3(100, 50, 0),  // 位置
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
		32.0f, 
		32.0f,
		CBarrierDurability::GUARD_FRAME
	);

	// 初期化結果を返す
	return S_OK;
}
//============================
// 終了処理
//============================
void CBarrierManager::Uninit(void)
{
	// 各種終了処理
}
//============================
// 更新処理
//============================
void CBarrierManager::Update(void)
{
	// nullじゃなかったら
	if (m_pBarrierUI)
	{
		// 耐久値に応じて変更
		switch (m_nBarrierNum)
		{
		case CBarrierDurability::GUARD_FRAME:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_FRAME); 
			break;

		case CBarrierDurability::GUARD_FIRST:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_FIRST); 
			break;

		case CBarrierDurability::GUARD_SECOND:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_SECOND); 
			break;

		case CBarrierDurability::GUARD_THIRD:
			m_pBarrierUI->SetTexture(CBarrierDurability::GUARD_THIRD); 
			break;
		}
	}
}
//============================
// バリア加算処理
//============================
void CBarrierManager::AddBarrier(int nValue)
{
	// 上限値以上なら
	if (m_nBarrierNum >= BARRIERINFO::MAX_GUARD) return;

	// 加算する
	m_nBarrierNum += nValue;
}
//============================
// バリア減算処理
//============================
void CBarrierManager::DamageBarrier(int nValue)
{
	// 耐久値を減らす
	m_nBarrierNum -= nValue;

	// 0以下なら
	if (m_nBarrierNum < 0) m_nBarrierNum = 0; // 最小制限
}
