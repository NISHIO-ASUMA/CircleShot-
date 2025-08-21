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

//**********************
// 定数宣言
//**********************
namespace CameraInfo
{
	constexpr float MAX_VIEWUP = 3.0f; // カメラの角度制限値
	constexpr float MAX_VIEWDOWN = 0.1f; // カメラの角度制限値
	constexpr float NorRot = D3DX_PI * 2.0f;	// 正規化値
	constexpr float CAMERABACKPOS = 350.0f;		// 後方カメラ
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
	m_isRotation = false;
	m_isStopRotation = false;
	m_isSetPos = false;
	m_lastBossPos = VECTOR3_NULL;
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
	m_pCamera.posV = D3DXVECTOR3(0.0f, 500.0f, -250.0f);		// カメラの位置
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

	// タイトルなら
	if (pMode == CScene::MODE_TITLE)
	{
		// タイトルカメラ作成
		TitleCamera();
	}
	else if (pMode == CScene::MODE_GAME)
	{
		// ロックオンにする
		m_pCamera.nMode = MODE_LOCKON;
	}

#ifdef _DEBUG
	// カメラモード変更
	if (pInput->GetTrigger(DIK_N))
	{
		m_pCamera.nMode = MODE_LOCKON;
	}
	if (pInput->GetTrigger(DIK_M))
	{
		m_pCamera.nMode = MODE_MOUSE;
	}
	if (pInput->GetTrigger(DIK_B))
	{
		m_pCamera.nMode = MODE_NONE;
	}
#endif
	
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


	// 角度の正規化
	if (m_pCamera.rot.y > D3DX_PI)
	{// D3DX_PIより大きくなったら
		m_pCamera.rot.y -= CameraInfo::NorRot;
	}

	// 角度の正規化
	if (m_pCamera.rot.y < -D3DX_PI)
	{// D3DX_PIより小さくなったら
		m_pCamera.rot.y += CameraInfo::NorRot;
	}
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

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_pCamera.mtxView,
		&m_pCamera.posV,
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

	// デバッグフォント
	CDebugproc::Print("Camera : PosV [ %.2f, %.2f, %.2f ]", m_pCamera.posV.x, m_pCamera.posV.y, m_pCamera.posV.z);
	CDebugproc::Draw(0, 100);

	CDebugproc::Print("Camera Mode { %d }",m_pCamera.nMode);
	CDebugproc::Draw(0, 420);
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
		if (m_pCamera.rot.x > CameraInfo::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CameraInfo::MAX_VIEWDOWN)
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
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// 回転量を制限
		if (m_pCamera.rot.x > CameraInfo::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CameraInfo::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// カメラの視点の情報
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}

	// 正規化
	if (m_pCamera.rot.y < -D3DX_PI)
	{
		m_pCamera.rot.y += CameraInfo::NorRot;
	}
	else if (m_pCamera.rot.y > D3DX_PI)
	{
		m_pCamera.rot.y += -CameraInfo::NorRot;
	}
	if (m_pCamera.rot.x < -D3DX_PI)
	{
		m_pCamera.rot.x += CameraInfo::NorRot;
	}
	else if (m_pCamera.rot.x > D3DX_PI)
	{
		m_pCamera.rot.x += -CameraInfo::NorRot;
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
	D3DXVECTOR3 VecSubToBoss = bossPos - SubPlayerPos;

	// 高さは無視
	VecSubToBoss.y = NULL;

	// ベクトルを正規化する
	D3DXVec3Normalize(&VecSubToBoss, &VecSubToBoss);

	// ボスへの角度を計算
	float fAngleSubToBoss = atan2f(-VecSubToBoss.x, -VecSubToBoss.z);

	// SUBプレイヤーの目的角度を設定
	pPlayerSub->SetRotDest(D3DXVECTOR3(0.0f, fAngleSubToBoss, 0.0f));

	// カメラ位置をMAINプレイヤーの後方へ
	D3DXVECTOR3 camOffset = -VecToBoss * CameraInfo::CAMERABACKPOS;

	// 高さを低めに設定
	camOffset.y = 140.0f;

	// カメラの目的位置
	D3DXVECTOR3 desiredPosV = playerPos + camOffset;

	// ターゲット座標を設定
	D3DXVECTOR3 targetBoss = bossPos;
	targetBoss.y = playerPos.y + 150.0f;  // 視点の上方向を強調

	// カメラに適用する
	m_pCamera.posV += (desiredPosV - m_pCamera.posV) * 0.3f;
	m_pCamera.posR += (targetBoss - m_pCamera.posR) * 0.3f;

	// ロックオン専用のカメラ角度を調整
	m_pCamera.rot.x = D3DX_PI * 0.42f;
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
	m_pCamera.posV = D3DXVECTOR3(-240.0f, 130.0f, 270.0f); // カメラの位置
	m_pCamera.posR = VECTOR3_NULL;	// カメラの見ている位置
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// 上方向ベクトル
	m_pCamera.rot = VECTOR3_NULL;	// 角度

	// 2体のタイトルプレイヤーの取得
	CTitlePlayer* pTplayer1 = CTitlePlayer::GetIdxPlayer(0);
	CTitlePlayer* pTplayer2 = CTitlePlayer::GetIdxPlayer(1);

	// nullチェック
	if (pTplayer1 == nullptr || pTplayer2 == nullptr) return;

	// 2体の中間点を回転の中心にする
	D3DXVECTOR3 pos1 = pTplayer1->GetPos();
	D3DXVECTOR3 pos2 = pTplayer2->GetPos();
	D3DXVECTOR3 centerPos = (pos1 + pos2) * 0.5f; 

	static float rotationAngle = 0.0f; // 回転用角度
	float radius = 300.0f;			// 回転半径
	float height = 170.0f;			// 高さ
	float stopAngle = D3DX_PI;		// プレイヤー正面
	float rotationSpeed = 0.04f;	// 回転スピード

	if (!m_isRotation)
	{
		// エンターキー押下で回転開始
		if ((CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN)) || (CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A)))
		{
			// フラグを有効化
			m_isRotation = true;

			// 回転リセット
			rotationAngle = 0.0f; 
		}
	}
	else
	{
		// カメラがまだ正面に来ていないなら回転
		if (rotationAngle < stopAngle)
		{
			// 回転角を加算
			rotationAngle += rotationSpeed;

			// カメラの視点情報
			m_pCamera.posV.x = centerPos.x + sinf(rotationAngle) * radius;
			m_pCamera.posV.z = centerPos.z + cosf(rotationAngle) * radius;
			m_pCamera.posV.y = centerPos.y + height;

			// 注視点を設定
			m_pCamera.posR = centerPos;
		}
		else
		{
			// 停止位置を固定
			rotationAngle = stopAngle;

			// カメラの視点情報
			m_pCamera.posV.x = centerPos.x + sinf(rotationAngle) * radius;
			m_pCamera.posV.z = centerPos.z + cosf(rotationAngle) * radius;
			m_pCamera.posV.y = centerPos.y + height;

			// 注視点を設定
			m_pCamera.posR = centerPos;

			// 終了フラグを有効化
			m_isStopRotation = true;
		}

		// カメラの上方向ベクトル
		m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
}
