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
#include "manager.h"
#include "player.h"
#include "gamemanager.h"
#include "rubblemanager.h"

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
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL,true,5,true);

	// クールタイムセット
	m_pBoss->SetCoolTime(m_CoolTime);
}
//===========================
// 待機状態更新処理
//===========================
void CBossStateNeutral::OnUpdate(void)
{
	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

	if (pCamera->GetMode() == CCamera::MODE_ANIM)
	{
		// クールタイム中はニュートラルモーション再生
		m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL, false, 0, false);

		return;
	}

	// クールタイム減算
	m_pBoss->DecCoolTime();

	// クールタイム終了時
	if (m_pBoss->GetCoolTime() <= 0)
	{
		// ランダムでパターンを決定
		int attackType = rand() % 5;

		switch (attackType)
		{
		case CBoss::TYPE_ACTION:  // 右手殴り
			m_pBoss->ChangeState(new CBosshandAttack(), ID_ACTION);
			return;

		case CBoss::TYPE_IMPACT: // 叩きつけ
			m_pBoss->ChangeState(new CBossimpactAttack(), ID_ACTION);
			return;

		case CBoss::TYPE_CIRCLE: // 薙ぎ払い
			m_pBoss->ChangeState(new CBosscircleAttack(), ID_ACTION);
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


//===========================
// コンストラクタ
//===========================
CBossStateEvent::CBossStateEvent()
{
	// IDセット
	SetID(ID_EVENT);
}
//===========================
// デストラクタ
//===========================
CBossStateEvent::~CBossStateEvent()
{
	//無し
}
//===========================
// イベント状態開始関数
//==========================
void CBossStateEvent::OnStart(void)
{
	// モーションセット
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_RUBBLE);

	// クールタイムセット
	m_pBoss->SetCoolTime(250);

	// マネージャー取得
	CRubbleManager* pRubble = CGameManager::GetRubble();
	if (pRubble == nullptr) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr) return;

	// プレイヤー取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (pPlayer == nullptr) return;

	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	playerPos.y = 0.0f;

	// 後方距離と高さ
	float backDistance = 590.0f;
	float heightOffset = 120.0f;

	// プレイヤーの向きの逆方向を取得
	float rotY = pPlayer->GetRotDest().y;
	D3DXVECTOR3 backwardVec = D3DXVECTOR3(-sinf(rotY), 0.0f, -cosf(rotY));

	// カメラ位置
	D3DXVECTOR3 camPos = playerPos + backwardVec * backDistance;
	camPos.y += heightOffset; // プレイヤーより少し上

	// 注視
	D3DXVECTOR3 targetPos = playerPos + D3DXVECTOR3(0.0f, 150.0f, 0.0f); // Yを大きくして見上げる

	// カメラチェンジ
	pCamera->SetCameraMode(pCamera->MODE_EVENT);

	// カメラの振動
	pCamera->ShakeCamera(240);

	// ランダムで出現する瓦礫のファイルを設定
	int nType = rand() % 3;

	// 瓦礫読み込み
	pRubble->LoadSplitFile(nType);

	// イベントカメラ開始
	pCamera->StartEventCamera(camPos, targetPos, 250);
}
//===========================
// イベント状態更新関数
//==========================
void CBossStateEvent::OnUpdate(void)
{
	// 現在のクールタイム取得
	int nCooltime = m_pBoss->GetCoolTime();

	// クールタイムがなくなったら
	if (nCooltime <= 0)
	{
		// 状態変更
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// ここで処理を返す
		return;
	}
}
//===========================
// イベント状態終了関数
//==========================
void CBossStateEvent::OnExit(void)
{
	// 無し
}
