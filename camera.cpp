//====================================
//
// カメラ処理 [ camera.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "object.h"
#include "boss.h"
#include "gamemanager.h"
#include "titleplayer.h"
#include "template.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

//**********************
// 定数宣言
//**********************
namespace CAMERAINFO
{
	constexpr float MAX_VIEWUP = 3.0f;			// カメラの角度制限値
	constexpr float MAX_VIEWDOWN = 0.1f;		// カメラの角度制限値
	constexpr float NorRot = D3DX_PI * 2.0f;	// 正規化値
	constexpr float CAMERABACKPOS = 450.0f;		// 後方カメラ
	constexpr float SHAKEVALUE = 12.0f;			// 振動の値
	constexpr float DIGITVALUE = 1000.0f;		// 割る値
	constexpr int RANDOMBASE = 2000;			// ランダム基準値
}

//=================================
// コンストラクタ
//=================================
CCamera::CCamera()
{
	// 値のクリア
	m_pCamera.mtxprojection = {};
	m_pCamera.mtxView = {};
	m_pCamera.posR = VECTOR3_NULL;
	m_pCamera.posV = VECTOR3_NULL;
	m_pCamera.rot = VECTOR3_NULL;
	m_pCamera.vecU = VECTOR3_NULL;
	m_pCamera.posRDest = VECTOR3_NULL;
	m_pCamera.fDistance = NULL;
	m_pCamera.nMode = MODE_NONE;
	m_pCamera.nUseKey = NULL;
	m_isRotation = false;
	m_isStopRotation = false;
	m_isSetPos = false;
	m_lastBossPos = VECTOR3_NULL;
	m_isShake = false;
	m_nShakeTime = NULL;
	m_isKey = false;

	// イベント用
	m_event.isActive = false;
	m_event.endFrame = NULL;
	m_event.frame = NULL;
	m_event.startPosR = VECTOR3_NULL;
	m_event.startPosV = VECTOR3_NULL;
	m_event.targetPosR = VECTOR3_NULL;
	m_event.targetPosV = VECTOR3_NULL;

	// アニメーション用
	m_pCamera.m_AnimData.isLoop = false;
	m_pCamera.m_AnimData.nNumKey = 20;

	// キー構造体変数のクリア
	for (int nCnt = 0; nCnt < NUMKEY; nCnt++)
	{
		m_pCamera.m_AnimData.KeyInfo[nCnt].fDistance = 780.0f;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].nAnimFrame = 40;
	}

	isAnimTime = false;
	m_nAnimNowKey = NULL;

}
//=================================
// デストラクタ
//=================================
CCamera::~CCamera()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CCamera::Init(void)
{
	// 初期値を設定する
	m_pCamera.posV = D3DXVECTOR3(0.0f, 500.0f, -600.0f);		// カメラの位置
	m_pCamera.posR = VECTOR3_NULL;								// カメラの見ている位置
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// 上方向ベクトル
	m_pCamera.rot = D3DXVECTOR3(D3DX_PI * 0.55f, 0.0f, 0.0f);	// 角度

	// 距離を計算
	float fRotx = m_pCamera.posV.x - m_pCamera.posR.x;
	float fRoty = m_pCamera.posV.y - m_pCamera.posR.y;
	float fRotz = m_pCamera.posV.z - m_pCamera.posR.z;

	// 視点から注視点までの距離
	m_pCamera.fDistance = sqrtf((fRotx * fRotx) + (fRoty * fRoty) + (fRotz * fRotz));

	// モードの初期化
	m_pCamera.nMode = MODE_NONE;

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CCamera::Uninit(void)
{
	// 無し
}
//=================================
// 更新処理
//=================================
void CCamera::Update(void)
{
	// 入力情報を取得
	CInputMouse* pMouse = CManager::GetMouse();
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	// 現在シーンの取得
	CScene::MODE pMode = CManager::GetScene();

	// イベントカメラモードなら
	if (m_pCamera.nMode == MODE_EVENT)
	{
		if (m_event.isActive)
		{
			m_event.frame++;

			float t = (float)m_event.frame / (float)m_event.endFrame;

			if (t > 1.0f) t = 1.0f;
			t = t * t * (3.0f - 2.0f * t);

			// 線形補間で目的位置に移動
			D3DXVECTOR3 newPosV = Lerp(m_event.startPosV, m_event.targetPosV, t);
			D3DXVECTOR3 newPosR = Lerp(m_event.startPosR, m_event.targetPosR, t);

			// シェイク処理
			if (m_isShake && m_nShakeTime > 0)
			{
				float fOffsetX = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE - 1.0f) * CAMERAINFO::SHAKEVALUE;
				float fOffsetY = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE - 1.0f) * CAMERAINFO::SHAKEVALUE;
				float fOffsetZ = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE - 1.0f) * CAMERAINFO::SHAKEVALUE;

				newPosV.x += fOffsetX;
				newPosV.y += fOffsetY;
				newPosV.z += fOffsetZ;

				m_nShakeTime--;

				if (m_nShakeTime <= 0)
					m_isShake = false;
			}

			m_pCamera.posV = newPosV;
			m_pCamera.posR = newPosR;

			if (m_event.frame >= m_event.endFrame)
			{
				m_event.isActive = false;

				m_pCamera.nMode = MODE_LOCKON;
			}

			// 角度正規化
			if (m_pCamera.rot.y > D3DX_PI) m_pCamera.rot.y -= CAMERAINFO::NorRot;
			if (m_pCamera.rot.y < -D3DX_PI) m_pCamera.rot.y += CAMERAINFO::NorRot;

			return;
		}
	}

	// タイトルなら
	if (pMode == CScene::MODE_TITLE)
	{
		// タイトルカメラ作成
		TitleCamera();
	}
	else if (pMode == CScene::MODE_TUTORIAL)
	{
		TutorialCamera();
	}
	else if (pMode == CScene::MODE_GAME)
	{
#ifdef _DEBUG

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_B))
		{
			// ロックオンにする
			m_pCamera.nMode = MODE_LOCKON;
		}

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_V))
		{
			// ロックオンにする
			m_pCamera.nMode = MODE_MOUSE;
		}
#else
		// 最初,アニメーションカメラにする,終了後にロックオンカメラ


		// ロックオンにする
		m_pCamera.nMode = MODE_LOCKON;

#endif // _DEBUG

	}
	else if (pMode == CScene::MODE_EDIT)
	{
		// ロックオンにする
		m_pCamera.nMode = MODE_MOUSE;
	}
	else if (pMode == CScene::MODE_CAMERAEDIT)
	{
		// 配置モードにする
		m_pCamera.nMode = MODE_ANIM;

		CCamera::MouseView(pMouse);

		// アニメーションセット
		CCamera::AnimCamera();
	}

	//if (m_pCamera.nMode == MODE_ANIM)
	//{
	//	UpdateAnimCamera();

	//	return;
	//}

	if (m_pCamera.nMode != MODE_EVENT)
	{
		switch (m_pCamera.nMode)
		{
		case MODE_NONE:
			break;

		case MODE_PLAYER:
			// プレイヤー追従
			PlayerFollow();
			break;

		case MODE_LOCKON:
			// ボスにロックオン
			LockOn();
			break;

		case MODE_MOUSE:
			// マウス視点移動
			MouseView(pMouse);
			break;

		default:
			break;
		}
	}

	// 角度の正規化
	if (m_pCamera.rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_pCamera.rot.y -= CAMERAINFO::NorRot;
	}

	// 角度の正規化
	if (m_pCamera.rot.y < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}

#ifdef _DEBUG

#endif // _DEBUG

}
//=================================
// カメラをセット
//=================================
void CCamera::SetCamera(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_pCamera.mtxView);

	// シェイク適用時
	D3DXVECTOR3 posVForView = m_pCamera.posV;

	if (m_isShake && (!m_event.isActive))
	{
		if (m_nShakeTime > 0)
		{
			float fOffsetX = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE ) * 25.0f;
			float fOffsetY = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE ) * 25.0f;
			float fOffsetZ = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE ) * 25.0f;

			posVForView.x += fOffsetX;
			posVForView.y += fOffsetY;
			posVForView.z += fOffsetZ;

			m_nShakeTime--;

			if (m_nShakeTime <= 0)
			{
				m_isShake = false;
				m_nShakeTime = 0;
			}
		}
		else
		{
			// 念のためフラグクリア
			m_isShake = false;
		}
	}
	
	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_pCamera.mtxView,
		&posVForView,
		&m_pCamera.posR,
		&m_pCamera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera.mtxView);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_pCamera.mtxprojection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_pCamera.mtxprojection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera.mtxprojection);

	// デバッグフォント取得
	CDebugproc* pDebug = CManager::GetRenderer()->GetDebug();
	if (pDebug == nullptr) return;


	// フォントセット
	CDebugproc::Print("Camera : PosV [ %.2f, %.2f, %.2f ]\n", m_pCamera.posV.x, m_pCamera.posV.y, m_pCamera.posV.z);
	// 描画開始
	CDebugproc::Draw(0, 20);

	CDebugproc::Print("Camera : Rot [ %.2f, %.2f, %.2f ]\n", m_pCamera.rot.x, m_pCamera.rot.y, m_pCamera.rot.z);
	CDebugproc::Draw(0, 40);

	if (m_pCamera.nMode == MODE_ANIM)
	{
		CDebugproc::Print("[ アニメーション構造体情報 ]");
		CDebugproc::Draw(0, 60);

		CDebugproc::Print("アニメーションキー数 : [ %d / %d ] ",m_nAnimNowKey, m_pCamera.m_AnimData.nNumKey);
		CDebugproc::Draw(0, 80);

		CDebugproc::Print("アニメーションカメラ座標 [ %.2f, %.2f, %.2f ]",
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVX, 
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVY, 
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVZ);
		CDebugproc::Draw(0, 100);

		CDebugproc::Print("アニメーションカメラ角度 [ %.2f, %.2f, %.2f ]",
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotX, 
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotY,
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotZ);
		CDebugproc::Draw(0, 120);

		CDebugproc::Print("アニメーションフレーム [ %d ]", m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame);
		CDebugproc::Draw(0, 140);

		CDebugproc::Print("現在編集中の番号 [ %d ]",m_nAnimNowKey);
		CDebugproc::Draw(0, 160);
	}
}
//======================================
// マウス操作の視点移動
//======================================
void CCamera::MouseView(CInputMouse * pMouse)
{
	// 右クリック
	if (pMouse->GetPress(CInputMouse::MOUSE_LEFT))
	{
		// マウスの移動量取得
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		// 現在の角度を計算
		D3DXVECTOR2 fAngle = Move - MoveOld;

		// 回転量を更新
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// 回転量を制限
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// カメラ座標を更新
		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.y = m_pCamera.posV.y + cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// 左クリック
	else if (pMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		D3DXVECTOR2 fAngle = Move - MoveOld;

		// 回転量を更新
		m_pCamera.rot.y += fAngle.x * 0.005f;
		m_pCamera.rot.x += fAngle.y * 0.005f;

		// 回転量を制限
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.005f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.005f;
		}

		// カメラの視点の情報
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}

	// 正規化
	if (m_pCamera.rot.y < -D3DX_PI)
	{
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.y > D3DX_PI)
	{
		m_pCamera.rot.y += -CAMERAINFO::NorRot;
	}
	if (m_pCamera.rot.x < -D3DX_PI)
	{
		m_pCamera.rot.x += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.x > D3DX_PI)
	{
		m_pCamera.rot.x += -CAMERAINFO::NorRot;
	}
}
//=================================
// ロックオン処理
//=================================
void CCamera::LockOn(void)
{
	// ボス取得
	CBoss* pBoss = CGameManager::GetBoss();

	// ボスが存在する
	if (pBoss && !m_isSetPos)
	{
		// 最終座標を保存
		m_lastBossPos = pBoss->GetPos();
		m_isSetPos = true;
	}
	
	// プレイヤー取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	CPlayer* pPlayerSub = CPlayer::GetIdxPlayer(1);

	// nullptrチェック
	if (pPlayer == nullptr || pPlayerSub == nullptr)
	{
		// ここで処理を返す
		return;
	}

	// MAINプレイヤー座標,SUBプレイヤー座標,ボス座標を取得
	D3DXVECTOR3 playerPos = pPlayer->GetPos();				// MAIN座標
	D3DXVECTOR3 SubPlayerPos = pPlayerSub->GetPos();		// SUB座標
	D3DXVECTOR3 bossPos = m_lastBossPos; //	ボス座標

	// MAINプレイヤー向き計算
	D3DXVECTOR3 VecToBoss = bossPos - playerPos;

	// 高さは無視
	VecToBoss.y = NULL;

	// ベクトルを正規化
	D3DXVec3Normalize(&VecToBoss, &VecToBoss);

	// ボスへの角度を計算
	float fAngleToBoss = atan2f(VecToBoss.x, VecToBoss.z);

	// プレイヤーの目的角に設定する
	pPlayer->SetRotDest(D3DXVECTOR3(0.0f, fAngleToBoss, 0.0f));

	// SUBプレイヤーの向き計算
	D3DXVECTOR3 VecSubToCenter = bossPos - SubPlayerPos;

	// 高さは無視
	VecSubToCenter.y = NULL;

	// ベクトルを正規化する
	D3DXVec3Normalize(&VecSubToCenter, &VecSubToCenter);

	// ボスへの角度を計算
	float fAngleSubToBoss = atan2f(-VecSubToCenter.x, -VecSubToCenter.z);

	// SUBプレイヤーの目的角度を設定
	pPlayerSub->SetRotDest(D3DXVECTOR3(0.0f, fAngleSubToBoss, 0.0f));

	// カメラ位置をMAINプレイヤーの後方へ
	D3DXVECTOR3 camOffset = -VecToBoss * CAMERAINFO::CAMERABACKPOS;

	// 高さを低めに設定
	camOffset.y = 187.0f;

	// カメラの目的位置
	D3DXVECTOR3 desiredPosV = playerPos + camOffset;

	// ターゲット座標を設定
	D3DXVECTOR3 targetBoss = bossPos;
	targetBoss.y = playerPos.y + 150.0f;	// 視点の上方向を強調

	// カメラに適用する
	m_pCamera.posV += (desiredPosV - m_pCamera.posV) * 0.3f;
	m_pCamera.posR += (targetBoss - m_pCamera.posR) * 0.3f;

	// ロックオン専用のカメラ角度を調整
	m_pCamera.rot.x = D3DX_PI * 0.08f;
}
//=================================
// プレイヤー追従処理
//=================================
void CCamera::PlayerFollow(void)
{
	// プレイヤー取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	CPlayer* pPlayerSub = CPlayer::GetIdxPlayer(1);

	// nullptrチェック
	if (pPlayer == nullptr || pPlayerSub == nullptr)
	{
		// ここで処理を返す
		return;
	}

	// 追従カメラ用に設定
	m_pCamera.posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRotDest().y) * 1.0f;
	m_pCamera.posRDest.y = pPlayer->GetPos().y + cosf(pPlayer->GetRotDest().y) * 1.0f;
	m_pCamera.posRDest.z = pPlayer->GetPos().z + cosf(pPlayer->GetRotDest().y) * 1.0f;

	m_pCamera.posR.x += ((m_pCamera.posRDest.x - m_pCamera.posR.x) * 0.3f);
	m_pCamera.posR.y += ((m_pCamera.posRDest.y - m_pCamera.posR.y) * 0.3f);
	m_pCamera.posR.z += ((m_pCamera.posRDest.z - m_pCamera.posR.z) * 0.3f);

	// カメラの視点の情報
	m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
	m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
	m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
}
//=================================
// 常に回転するカメラの処理
//=================================
void CCamera::Rotation(void)
{
	m_pCamera.posV.z = -500.0f;
	m_pCamera.posV.y = 800.0f;

	m_pCamera.rot.y += 0.005f; // カメラの視点の情報
	m_pCamera.rot.x = D3DX_PI * 0.75f;
	m_pCamera.fDistance = 1000.0f;

	m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
	m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
	m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
}
//=================================
// タイトルカメラ処理
//=================================
void CCamera::TitleCamera(void)
{
	// タイトルカメラ用に設定
	m_pCamera.posV = D3DXVECTOR3(0.0f, 150.0f, -950.0f); // カメラの位置
	m_pCamera.posR = VECTOR3_NULL;						 // カメラの見ている位置
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 // 上方向ベクトル
	m_pCamera.rot = VECTOR3_NULL;						 // 角度

	if (!m_isRotation)
	{
		// Enterキー　or Startボタン押下
		if ((CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN)) || (CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START)))
		{
			// フラグを有効化
			m_isRotation = true;
		}
	}
	else if ((m_isRotation && CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN)) || (CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START)))
	{
		m_isKey = true;
	}
}
//=================================
// チュートリアルカメラ関数
//=================================
void CCamera::TutorialCamera(void)
{
	if (!m_isSetPos)
	{
		// 最終座標を保存
		m_lastBossPos = VECTOR3_NULL;
		m_isSetPos = true;
	}
	

	// プレイヤー取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	CPlayer* pPlayerSub = CPlayer::GetIdxPlayer(1);

	// nullptrチェック
	if (pPlayer == nullptr || pPlayerSub == nullptr)
	{
		// ここで処理を返す
		return;
	}

	// 2体のプレイヤーの座標取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();			// MAIN座標
	D3DXVECTOR3 SubPlayerPos = pPlayerSub->GetPos();	// SUB座標

	//プレイヤー向き計算
	D3DXVECTOR3 VecToCenter = VECTOR3_NULL - PlayerPos;

	// 高さは無視
	VecToCenter.y = NULL;

	// ベクトルを正規化
	D3DXVec3Normalize(&VecToCenter, &VecToCenter);

	// 中心への角度
	float fAngleToCenter = atan2f(VecToCenter.x, VecToCenter.z);

	// プレイヤーの目的角に設定する
	pPlayer->SetRotDest(D3DXVECTOR3(0.0f, fAngleToCenter, 0.0f));

	// SUBプレイヤーの向き計算
	D3DXVECTOR3 VecSubToCenter = VECTOR3_NULL - SubPlayerPos;

	// 高さは無視
	VecSubToCenter.y = NULL;

	// ベクトルを正規化する
	D3DXVec3Normalize(&VecSubToCenter, &VecSubToCenter);

	// 中心への角度
	float fAngleSubToCenter = atan2f(-VecSubToCenter.x, -VecSubToCenter.z);

	// SUBプレイヤーの目的角度を設定
	pPlayerSub->SetRotDest(D3DXVECTOR3(0.0f, fAngleSubToCenter, 0.0f));

	// カメラ位置をMAINプレイヤーの後方へ
	D3DXVECTOR3 BackCamera = -VecToCenter * CAMERAINFO::CAMERABACKPOS;

	// 高さを低めに設定
	BackCamera.y = 190.0f;

	// カメラの目的位置
	D3DXVECTOR3 DestPosV = PlayerPos + BackCamera;

	// ターゲット座標を設定
	D3DXVECTOR3 TargetPos = VECTOR3_NULL;
	TargetPos.y = PlayerPos.y + 150.0f;  // 視点の上方向を強調

	// カメラに適用する
	m_pCamera.posV += (DestPosV - m_pCamera.posV) * 0.3f;
	m_pCamera.posR += (TargetPos - m_pCamera.posR) * 0.3f;

	// ロックオン専用のカメラ角度を調整
	m_pCamera.rot.x = D3DX_PI * 0.08f;
}

//=================================
// 振動カメラ関数
//=================================
void CCamera::ShakeCamera(int WaveTime)
{
	if (WaveTime <= 0) return;

	m_isShake = true;
	m_nShakeTime = WaveTime;
}
//=================================
// イベントカメラを開始する関数
//=================================
void CCamera::StartEventCamera(const D3DXVECTOR3& targetV, const D3DXVECTOR3& targetR, int endFrame)
{
	m_event.isActive = true;
	m_event.frame = 0;
	m_event.endFrame = endFrame;

	m_event.startPosV = m_pCamera.posV;
	m_event.startPosR = m_pCamera.posR;
	m_event.targetPosV = targetV;
	m_event.targetPosR = targetR;

	// カメラモードをイベントに切り替え
	m_pCamera.nMode = MODE_EVENT;
}

//=================================
// アニメーション配置関数
//=================================
void CCamera::AnimCamera(void)
{
	// 上移動
	if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true)
	{
		m_pCamera.posV.x += sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.z += cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// 下移動
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true)
	{
		m_pCamera.posV.x -= sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.z -= cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// 左移動
	if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true)
	{
		m_pCamera.posV.z += sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.x -= cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// 右移動
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true)
	{
		m_pCamera.posV.z -= sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.x += cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}

	// フレーム数の変更
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_UP))
	{
		// 加算
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN) && m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame > 1)
	{
		// 減算
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame--;

		if (m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame <= 0)
		{
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame = 0;
		}
	}

	// フレーム数の変更
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RIGHT))
	{
		// 加算
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame += 10;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_LEFT) && m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame > 1)
	{
		// 減算
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame -= 10;

		if (m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame <= 0)
		{
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame = 0;
		}
	}

	// 配置の登録
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{// 情報を配列に追加する
		// 座標
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVX = m_pCamera.posV.x;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVY = m_pCamera.posV.y;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVZ = m_pCamera.posV.z;

		// 注視点座標
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRX = m_pCamera.posR.x;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRY = m_pCamera.posR.y;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRZ = m_pCamera.posR.z;

		// 角度情報
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotX = m_pCamera.rot.x;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotY = m_pCamera.rot.y;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotZ = m_pCamera.rot.z;

		// 距離
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fDistance = m_pCamera.fDistance;

		// 配列をずらす
		m_nAnimNowKey = (m_nAnimNowKey + 1) % m_pCamera.m_AnimData.nNumKey;
	}

	// 配置の書き出し
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F7))
	{
		// 保存関数実行
		Save();
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F5))
	{
		Load();
		UpdateAnimCamera();
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_TAB))
	{
		// 場所リセット
		m_pCamera.posV = D3DXVECTOR3(0.0f, 150.0f, -950.0f); // カメラの位置
		m_pCamera.posR = VECTOR3_NULL;						 // カメラの見ている位置
		m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 // 上方向ベクトル
		m_pCamera.rot = VECTOR3_NULL;						 // 角度
	}
}

//=================================
// 読み込み関数
//=================================
void CCamera::Load(void)
{
	// 指定ファイルを開く
	std::ifstream LoadFile("data\\Loader\\CameraInfo.txt");

	// もしファイルが開けない場合
	if (!LoadFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", "data\\Loader\\CameraInfo.txt", MB_OK);

		return;
	}

	std::string token;

	int keyIndex = 0;

	while (LoadFile >> token)
	{
		if (token == "LOOP")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.isLoop;
		}
		else if (token == "NUM_ALLKEY")
		{
			LoadFile >> token; // "="

			// 使うキー数
			LoadFile >> m_pCamera.nUseKey;

			// 配列最大数チェック
			if (m_pCamera.nUseKey > NUMKEY)
				m_pCamera.nUseKey = NUMKEY;
		}
		else if (token == "FRAME")
		{
			LoadFile >> token; // "="

			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].nAnimFrame;
		}
		else if (token == "POSV")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosVX
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosVY
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosVZ;
		}
		else if (token == "POSR")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosRX
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosRY
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosRZ;
		}
		else if (token == "ROT")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fRotX
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fRotY
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fRotZ;
		}
		else if (token == "DISTANCE")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fDistance;
		}
		else if (token == "END_KEYSET")
		{
			// キー加算
			keyIndex++;
		}
		else if (token == "END_ANIMCAMERA")
		{
			// ファイル終了
			break;
		}
	}

	// ファイル閉じる
	LoadFile.close();
}
//=================================
// 書き出し関数
//=================================
void CCamera::Save(void)
{
	// 指定ファイルを開く
	std::ofstream outFile("data\\Loader\\CameraInfo.txt");

	// もしファイルが開けない場合
	if (!outFile)
	{
		MessageBox(NULL, "ファイルオープン失敗", "data\\Loader\\CameraInfo.txt", MB_OK);

		return;
	}

	// float出力を固定小数点形式にする
	outFile << std::fixed << std::setprecision(2);

	outFile << "//==============================================================\n";
	outFile << "// \n";
	outFile << "// カメラアニメーションテキスト [ data\\Loader\\CameraInfo.txt ]\n";
	outFile << "// Author : Asuma Nishio\n";
	outFile << "// \n";
	outFile << "//==============================================================\n\n";

	outFile << "//==========================================================\n";
	outFile << "// アニメーション情報\n";
	outFile << "//==========================================================\n\n";

	outFile << " LOOP = " << m_pCamera.m_AnimData.isLoop << "\n";	// ループ情報
	outFile << " NUM_ALLKEY = " << m_nAnimNowKey << "\n\n";	// 最大キー数

	// 各配列のキー情報
	for (int nCnt = 0; nCnt < m_nAnimNowKey; nCnt++)
	{
		// 開始
		outFile << "\tKEYSET\t\t# --- << KEY  " << nCnt << " / " << m_nAnimNowKey << " >> --- \n";

		// キーフレーム
		outFile << "\t\tFRAME = " << m_pCamera.m_AnimData.KeyInfo[nCnt].nAnimFrame << "\n";

		// 座標
		outFile << "\t\tPOSV = "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVX << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVY << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVZ << "\n";

		// 注視点座標
		outFile << "\t\tPOSR = "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRX << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRY << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRZ << "\n";

		// 角度
		outFile << "\t\tROT = "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fRotX << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fRotY << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fRotZ << "\n";

		// カメラの距離
		outFile << "\t\tDISTANCE = " << m_pCamera.m_AnimData.KeyInfo[nCnt].fDistance << "\n";

		// キーセット終了
		outFile << "\tEND_KEYSET\n\n";
	}

	outFile << "END_ANIMCAMERA\n";

	// 閉じる
	outFile.close();
}

//=================================
// アニメーション更新関数
//=================================
void CCamera::UpdateAnimCamera(void)
{
	// motion更新と同じようにやる

}
