//=====================================
//
// ボス状態管理処理 [ bossstate.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "bossstate.h"
#include "bossattackstate.h"

//===========================
// コンストラクタ
//===========================
CBossStateBace::CBossStateBace()
{
	// 値のクリア
	m_ID = ID_NEUTRAL;
	m_pBoss = nullptr;
}
//===========================
// デストラクタ
//===========================
CBossStateBace::~CBossStateBace()
{
	// 無し
}


//===========================
// 待機状態コンストラクタ
//===========================
CBossStateNeutral::CBossStateNeutral(int nTime) : m_CoolTime(nTime), m_nCurrentState(0)
{
	// IDセット
	SetID(ID_NEUTRAL);
}
//===========================
// 待機状態デストラクタ
//===========================
CBossStateNeutral::~CBossStateNeutral()
{
	// 無い
}
//===========================
// 待機状態開始処理
//===========================
void CBossStateNeutral::OnStart(void)
{
	// モーションセット
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL,false,0,false);

	// クールタイムセット
	m_pBoss->SetCoolTime(m_CoolTime);
}
//===========================
// 待機状態更新処理
//===========================
void CBossStateNeutral::OnUpdate(void)
{
	// 減算
	m_pBoss->DecCoolTime();

	if (m_pBoss->GetCoolTime() <= 0)
	{
		// ランダムでパターンを決定
		int attackType = rand() % CBoss::PATTERN_MAX;

		switch (attackType)
		{
		case CBoss::PATTERN_HAND:  // 殴り
			m_pBoss->ChangeState(new CBosshandAttack(), ID_ACTION);
			return;

		case CBoss::PATTERN_IMPACT: // 叩きつけ
			m_pBoss->ChangeState(new CBossimpactAttack(), ID_ACTION);
			return;
		}
	}
	else
	{
		// クールタイム中はニュートラルモーション再生
		m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL, false, 0,false);
	}
}
//===========================
// 待機状態終了処理
//===========================
void CBossStateNeutral::OnExit(void)
{
	// 無し
}
