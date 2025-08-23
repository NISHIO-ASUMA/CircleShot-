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
	// 初期化結果を返す
	return S_OK;
}
//============================
// 終了処理
//============================
void CBarrierManager::Uninit(void)
{

}
//============================
// 更新処理
//============================
void CBarrierManager::Update(void)
{
	// UI生成
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
