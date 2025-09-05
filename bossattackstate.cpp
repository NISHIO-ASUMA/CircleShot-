//===============================================
//
// ボスの攻撃状態管理処理 [bossattackstate.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**************************
// インクルードファイル宣言
//**************************
#include "state.h"
#include "bossattackstate.h"

//====================================
// オーバーロードコンストラクタ
//====================================
CBosshandAttack::CBosshandAttack()
{
	// IDセット
	SetID(ID_ACTION);
}
//====================================
// オーバーロードデストラクタ
//====================================
CBosshandAttack::~CBosshandAttack()
{
	// 無い
}
//====================================
// 開始処理
//====================================
void CBosshandAttack::OnStart(void)
{
	// フレーム初期化
	m_pBoss->GetMotion()->SetResetFrame(NULL);

	// 向かせる
	m_pBoss->RollToPlayer();

	// モーションセット
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_ACTION);

	// クールタイムセット
	m_pBoss->SetCoolTime(180);
}
//====================================
// 更新処理
//====================================
void CBosshandAttack::OnUpdate(void)
{
	// 現在のクールタイム取得
	int nCooltime = m_pBoss->GetCoolTime();

	if (nCooltime <= 0)
	{
		// 状態変更
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// ここで処理を返す
		return;
	}
}
//====================================
// 終了処理
//====================================
void CBosshandAttack::OnExit(void)
{
	// 無し
}



//====================================
// オーバーロードコンストラクタ
//====================================
CBossimpactAttack::CBossimpactAttack()
{
	// IDをセット
	SetID(ID_ACTION);
}
//====================================
// デストラクタ
//====================================
CBossimpactAttack::~CBossimpactAttack()
{
	// 無し
}
//====================================
// ステート開始処理
//====================================
void CBossimpactAttack::OnStart(void)
{
	// フレーム初期化
	m_pBoss->GetMotion()->SetResetFrame(NULL);

	// 向かせる
	m_pBoss->RollToPlayer();

	// モーションセット
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_IMPACT);

	// クールタイムセット
	m_pBoss->SetCoolTime(160);
}
//====================================
// ステート更新処理
//====================================
void CBossimpactAttack::OnUpdate(void)
{
	// 現在のクールタイム取得
	int nCooltime = m_pBoss->GetCoolTime();

	// 終了判定かつ クールタイムがなくなったら
	if (nCooltime <= 0)
	{
		// 状態変更
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// ここで処理を返す
		return;
	}
}
//====================================
// ステート終了処理
//====================================
void CBossimpactAttack::OnExit(void)
{
	// 無し
}

//====================================
// オーバーロードコンストラクタ
//====================================
CBosscircleAttack::CBosscircleAttack()
{
	// IDをセット
	SetID(ID_ACTION);
}
//====================================
// デストラクタ
//====================================
CBosscircleAttack::~CBosscircleAttack()
{
	// 無し
}
//====================================
// ステート開始関数
//====================================
void CBosscircleAttack::OnStart(void)
{
	// フレーム初期化
	m_pBoss->GetMotion()->SetResetFrame(NULL);

	// 向かせる
	m_pBoss->RollToPlayer();

	// モーションセット
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_CIRCLE);

	// クールタイムセット
	m_pBoss->SetCoolTime(295);
}
//====================================
// ステート更新関数
//====================================
void CBosscircleAttack::OnUpdate(void)
{
	// 現在のクールタイム取得
	int nCooltime = m_pBoss->GetCoolTime();

	// 終了判定かつ クールタイムがなくなったら
	if (nCooltime <= 0)
	{
		// 状態変更
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// ここで処理を返す
		return;
	}
}
//====================================
// ステート終了関数
//====================================
void CBosscircleAttack::OnExit(void)
{
	// 無し
}
