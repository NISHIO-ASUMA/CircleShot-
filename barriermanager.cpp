//=====================================================
//
// バリアオブジェクトの管理処理 [ barriermanager.cpp ]
// Author : Asuma Nishio
//
//=====================================================

//*********************************
// インクルードファイル
//*********************************
#include "barriermanager.h"
#include "barrierdurability.h"

//============================
// コンストラクタ
//============================
CBarrierManager::CBarrierManager()
{
	// 値のクリア
	m_nBarrierNum = NULL;

	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		m_pBarrierObj[nCnt] = nullptr;
	}
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
	// 無し
}
//============================
// 更新処理
//============================
void CBarrierManager::Update(void)
{
	// 無し
}
//============================
// バリア加算処理
//============================
void CBarrierManager::AddBarrier(int nValue, D3DXVECTOR3 playerPos,float fRadius)
{
	// 上限値以上なら
	if (m_nBarrierNum >= MAX_GUARD)
	{
		// 最大値に設定
		m_nBarrierNum = MAX_GUARD;

		return;
	}

	// 加算する
	m_nBarrierNum += nValue;

	// バリア生成
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		if (nCnt < m_nBarrierNum)
		{
			// まだ生成されていない場合のみ作成
			if (m_pBarrierObj[nCnt] == nullptr)
			{
				// 角度を計算する
				float angle = (float)nCnt / m_nBarrierNum * D3DX_PI * 2.0f;

				// バリア座標を設定する
				D3DXVECTOR3 barrierPos;

				barrierPos.x = playerPos.x + cosf(angle) * fRadius;
				barrierPos.y = playerPos.y;
				barrierPos.z = playerPos.z + sinf(angle) * fRadius;

				// バリアオブジェクトを生成
				m_pBarrierObj[nCnt] = CBarrierDurability::Create(
					barrierPos,
					VECTOR3_NULL,
					"data\\MODEL\\STAGEOBJ\\Difence000.x");

				// インデックスセット
				m_pBarrierObj[nCnt]->SetIdx(nCnt);
			}
		}
		else
		{
			// 不要になったバリアは削除
			if (m_pBarrierObj[nCnt] != nullptr)
			{
				// 終了処理
				m_pBarrierObj[nCnt]->Uninit();

				// null初期化
				m_pBarrierObj[nCnt] = nullptr;
			}
		}
	}
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

	  // 不要になったバリアを削除
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		// バリア数より大きいとき
		if (nCnt >= m_nBarrierNum)
		{
			// nullチェック
			if (m_pBarrierObj[nCnt] != nullptr)
			{
				// 終了処理
				m_pBarrierObj[nCnt]->Uninit();

				// null初期化
				m_pBarrierObj[nCnt] = nullptr;
			}
		}
	}
}
