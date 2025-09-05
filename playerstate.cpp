//=============================================
//
// プレイヤー状態管理処理 [ playerstate.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// インクルードファイル宣言
//**************************
#include "playerstate.h"
#include "state.h"
#include "manager.h"
#include "gamemanager.h"
#include "parameter.h"
#include "pausemanager.h"

//******************************
// 定数宣言
//******************************
constexpr int DAMAGECOUNT = 60;	// 最大ステートカウント

//==================================
// プレイヤー状態コンストラクタ
//==================================
CPlayerStateBase::CPlayerStateBase()
{
	// 値のクリア
	m_pPlayer = nullptr;
	m_ID = ID_NEUTRAL;
}
//==================================
// プレイヤー状態デストラクタ
//==================================
CPlayerStateBase::~CPlayerStateBase()
{
	// 無し
}


//==================================
// 待機状態時コンストラクタ
//==================================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// セット
	SetID(ID_NEUTRAL);
}
//==================================
// 待機状態時デストラクタ
//==================================
CPlayerStateNeutral::~CPlayerStateNeutral()
{
	// 無し
}
//==================================
// 待機状態開始関数
//==================================
void CPlayerStateNeutral::OnStart()
{
	// ニュートラルモーションに設定
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_NEUTRAL, true, 5, false);
}
//==================================
// 待機状態更新関数
//==================================
void CPlayerStateNeutral::OnUpdate()
{
	// キー入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモードなら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// 移動入力があれば移動状態へ
	if ((m_pPlayer->isMoveInputKey(pInput) || m_pPlayer->isMovePadButton(pPad)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// 状態変更
		m_pPlayer->ChangeState(new CPlayerStateMove, ID_MOVE);

		// ここで処理を返す
		return;
	}

	// 攻撃キー入力時
	if ((pInput->GetPress(DIK_RETURN) || pPad->GetPress(CJoyPad::JOYKEY_X)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// ステート変更
		m_pPlayer->ChangeState(new CPlayerStateAction, ID_ACTION);

		// ここで処理を返す
		return;
	}

	// Spaceキー もしくは PadのAキー
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// ステート変更
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// ここで処理を返す
		return;
	}
}
//==================================
// 待機状態時終了関数
//==================================
void CPlayerStateNeutral::OnExit()
{
	// 無し
}


//==================================
// コンストラクタ
//==================================
CPlayerStateAction::CPlayerStateAction()
{
	// セット
	SetID(ID_ACTION);
}
//==================================
// デストラクタ
//==================================
CPlayerStateAction::~CPlayerStateAction()
{
	// 無し
}
//==================================
// 攻撃状態開始関数
//==================================
void CPlayerStateAction::OnStart()
{
	// 攻撃モーションに変更
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_ACTION);
}
//==================================
// 攻撃状態更新関数
//==================================
void CPlayerStateAction::OnUpdate()
{
	// シーン取得
	CScene::MODE nMode = CManager::GetScene();

	// 入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad * pPad = CManager::GetJoyPad();

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモードなら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// 重力
	m_pPlayer->GravityScal();

	// 武器の位置取得
	CModel* pModelWeapon = m_pPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// nullだったら
	if (!pModelWeapon) return;

	// 腕のワールドマトリックスを取得
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	if (nMode == CScene::MODE_GAME)
	{
		// プレイヤーとボス間でベクトル生成
		D3DXVECTOR3 VecBoss = m_pPlayer->VecToBoss(m_pPlayer->GetPos());

		// 攻撃更新
		m_pPlayer->UpdateAction(pInput, mtxWorld, VecBoss, pPad);
	}
	else if (nMode == CScene::MODE_TUTORIAL)
	{
		// プレイヤーと中心でベクトル生成
		D3DXVECTOR3 VecCenter = m_pPlayer->VecToCenter(m_pPlayer->GetPos());

		// 攻撃更新
		m_pPlayer->UpdateAction(pInput, mtxWorld, VecCenter, pPad);
	}
}
//==================================
// 攻撃状態終了関数
//==================================
void CPlayerStateAction::OnExit()
{
	// 無し
}


//==================================
// 移動状態コンストラクタ
//==================================
CPlayerStateMove::CPlayerStateMove()
{
	// セット
	SetID(ID_MOVE);
}
//==================================
// 移動状態デストラクタ
//==================================
CPlayerStateMove::~CPlayerStateMove()
{
	// 無し
}
//==================================
// 移動状態開始関数
//==================================
void CPlayerStateMove::OnStart()
{
	// 無し
}
//==================================
// 移動状態更新関数
//==================================
void CPlayerStateMove::OnUpdate()
{
	// キー入力を取得	
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモードなら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// シーン取得
	CScene::MODE nMode = CManager::GetScene();
	D3DXVECTOR3 MeshPos = VECTOR3_NULL;

	if (nMode == CScene::MODE_GAME)
	{
		// シリンダー座標の取得
		MeshPos = CGameManager::GetCylinder()->GetPos();

	}
	else
	{
		// シリンダー座標の取得
		MeshPos = VECTOR3_NULL;
	}

	// 移動処理実行
	m_pPlayer->UpdateMove(MeshPos, pInput, pPad);

	// キー入力が無い
	if (!m_pPlayer->isMoveInputKey(pInput) && !m_pPlayer->isMovePadButton(pPad)
		&& m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// ニュートラルに遷移
		m_pPlayer->ChangeState(new CPlayerStateNeutral, ID_NEUTRAL);

		// ここで処理を返す
		return;
	}

	// ジャンプキー入力時にステート変更
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE		   &&
		!m_pPlayer->IsJumping())
	{
		// ジャンプに遷移
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// ここで処理を返す
		return;
	}
}
//==================================
// 移動状態終了関数
//==================================
void CPlayerStateMove::OnExit()
{
	// 無し
}

//==================================
// ダメージ状態コンストラクタ
//==================================
CPlayerStateDamage::CPlayerStateDamage(int nDamage)
{
	// id変更
	SetID(ID_DAMAGE);

	// 値のクリア
	m_nStateCount = NULL;
	m_nDamage = nDamage;
}
//==================================
// ダメージ状態デストラクタ
//==================================
CPlayerStateDamage::~CPlayerStateDamage()
{
	// 無し
}
//==================================
// ダメージ状態開始関数
//==================================
void CPlayerStateDamage::OnStart()
{
	// モーションセット
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_DAMAGE, false, 0, false);

	// 一体目のプレイヤーの時
	if (m_pPlayer->GetPlayerIndex() == 0)
	{
		// 体力を減らす
		m_pPlayer->HitDamage(m_nDamage);
	}

	// 状態変更
	m_nStateCount = DAMAGECOUNT;
}
//==================================
// ダメージ状態更新関数
//==================================
void CPlayerStateDamage::OnUpdate()
{
	// 空中時,重力
	m_pPlayer->GravityScal();

	// 位置更新
	m_pPlayer->AddMove();

	// 状態管理カウンターをデクリメント
	m_nStateCount--;

	if (m_nStateCount <= NULL)
	{
		// カウントを変更
		m_nStateCount = DAMAGECOUNT; 

		// 状態変更
		m_pPlayer->ChangeState(new CPlayerStateNeutral(), ID_NEUTRAL);

		// ここで処理を返す
		return;
	}
}
//==================================
// ダメージ状態更新関数
//==================================
void CPlayerStateDamage::OnExit()
{
	// 無し
}


//==================================
// ジャンプ状態時コンスタラクタ
//==================================
CPlayerStateJump::CPlayerStateJump()
{
	// IDをセット
	SetID(ID_JUMP);
}
//==================================
// ジャンプ状態時デストラクタ
//==================================
CPlayerStateJump::~CPlayerStateJump()
{
	// 無し
}
//==================================
// ジャンプ状態時開始関数
//==================================
void CPlayerStateJump::OnStart()
{
	// ジャンプ開始
	m_pPlayer->StartJump();

	// ジャンプモーションに変更
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_JUMP);
}
//==================================
// ジャンプ状態時更新関数
//==================================
void CPlayerStateJump::OnUpdate()
{
	// 入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// 武器の位置取得
	CModel* pModelWeapon = m_pPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// nullだったら
	if (!pModelWeapon) return;

	// 腕のワールドマトリックスを取得
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	// シーン取得
	CScene::MODE nMode = CManager::GetScene();

	// ゲームシーン
	if (nMode == CScene::MODE_GAME)
	{
		// プレイヤーとボス間でベクトル生成
		D3DXVECTOR3 VecBoss = m_pPlayer->VecToBoss(m_pPlayer->GetPos());

		// ジャンプ更新関数
		m_pPlayer->UpdateJumpAction(pInput, mtxWorld, VecBoss, pPad);
	}
	// チュートリアルシーン
	else if (nMode == CScene::MODE_TUTORIAL)
	{
		// 中心ベクトル生成
		D3DXVECTOR3 VecCenter = m_pPlayer->VecToCenter(m_pPlayer->GetPos());

		// ジャンプ更新関数
		m_pPlayer->UpdateJumpAction(pInput, mtxWorld, VecCenter, pPad);
	}

}
//==================================
// ジャンプ状態時終了関数
//==================================
void CPlayerStateJump::OnExit()
{
	// ジャンプを未使用
	m_pPlayer->SetJump(false);

	// 着地を未使用
	m_pPlayer->SetLanding(true);
}


//==================================
// ガード状態時コンスタラクタ
//==================================
CPlayerStateGuard::CPlayerStateGuard()
{
	// IDをセット
	SetID(ID_GUARD);
}
//==================================
// ガード状態時デストラクタ
//==================================
CPlayerStateGuard::~CPlayerStateGuard()
{
	// 無し
}
//==================================
// ガード状態時開始関数
//==================================
void CPlayerStateGuard::OnStart()
{
	// モーション変更
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_GUARD);
}
//==================================
// ガード状態時更新関数
//==================================
void CPlayerStateGuard::OnUpdate()
{
	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモードなら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// ステート変更
	m_pPlayer->ChangeState(new CPlayerStateNeutral(), ID_NEUTRAL);

	// ここで処理を返す
	return;

}
//==================================
// ガード状態時終了関数
//==================================
void CPlayerStateGuard::OnExit()
{
	// 無し
}
