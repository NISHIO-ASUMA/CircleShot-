//====================================
//
// ボス処理 [ boss.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "boss.h"
#include "debugproc.h"
#include "manager.h"
#include "parameter.h"
#include "result.h"
#include <ctime>
#include "meshimpact.h"
#include "particle.h"
#include "bossstate.h"
#include "state.h"
#include "attacksign.h"
#include "player.h"

//****************************
// 定数宣言
//****************************
constexpr float HITRANGE = 12.0f; // コリジョンサイズ
constexpr int COOLTIME = 60;	  // 初期クールタイム

//****************************
// 静的メンバ変数宣言
//****************************
bool CBoss::m_isdaeth = false;    // 死亡フラグ

//====================================
// オーバーロードコンストラクタ
//====================================
CBoss::CBoss(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;

	m_pMotion = nullptr;
	m_pParam = nullptr;
	m_pState = nullptr;

	m_type = NULL;
	m_nCoolTime = NULL;
	m_mtxworld = {};

	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_fSize = NULL;
	m_isAttacked = false;
	m_nCurrentMotion = PATTERN_NONE;
}
//====================================
// デストラクタ
//====================================
CBoss::~CBoss()
{
	// 無し
}
//====================================
// 生成処理
//====================================
CBoss* CBoss::Create(D3DXVECTOR3 pos,float fSize,int nLife)
{
	// インスタンス生成
	CBoss* pBoss = new CBoss;

	// 生成失敗時
	if (pBoss == nullptr) return nullptr;

	// オブジェクトセット
	pBoss->m_pos = pos;
	pBoss->m_fSize = fSize;

	// 初期化失敗時
	if (FAILED(pBoss->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// パラメーター設定
	pBoss->m_pParam = new CParameter;

	// nullじゃなかったら
	if (pBoss->m_pParam != nullptr) pBoss->m_pParam->SetHp(nLife);

	// ポインタを返す
	return pBoss;
}
//=========================================
// モデルの特定部分パーツの取得関数
//=========================================
CModel* CBoss::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// ボスが持っているモデルの数の中から探す
	for (int nModel = 0; nModel < NUMMODELS; nModel++)
	{
		// モデルがある かつ 取得したい物と一致していたら
		if (m_pModel[nModel] && m_pModel[nModel]->GetPartType() == modelpart)
		{
			// 該当モデルのidx番号のモデルを返す
			return m_pModel[nModel];
		}
	}

	// 該当なしの場合
	return nullptr;
}
//====================================
// 初期化処理
//====================================
HRESULT CBoss::Init(void)
{
	// フラグを初期化
	m_isdaeth = false;

	// オブジェクトの種類をセット
	SetObjType(TYPE_BOSS);

	// タイプ代入
	m_type = CBoss::TYPE_MAX;

	// 初期クールタイムを設定
	m_nCoolTime = COOLTIME;

	// モーションの読み込み
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\Bossmotion.txt", NUMMODELS, m_pModel, CBoss::TYPE_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(m_type);

	// ステート生成
	m_pState = new CStateMachine;

	// 初期状態をセット
	ChangeState(new CBossStateNeutral(120), CBossStateBace::ID_NEUTRAL);

	// 初期化結果を返す
	return S_OK;
}
//====================================
// 終了処理
//====================================
void CBoss::Uninit(void)
{
	// モデル数分の破棄
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		// nullptrチェック
		if (m_pModel[nCnt] != nullptr)
		{
			// 終了処理
			m_pModel[nCnt]->Uninit();

			// ポインタの破棄
			delete m_pModel[nCnt];

			// nullptrにする
			m_pModel[nCnt] = nullptr;
		}
	}

	// nullptrチェック
	if (m_pMotion != nullptr)
	{
		// ポインタの破棄
		delete m_pMotion;

		// nullptrにする
		m_pMotion = nullptr;
	}

	// nullptrチェック
	if (m_pParam != nullptr)
	{
		// ポインタの破棄
		delete m_pParam;

		// nullptrにする
		m_pParam = nullptr;
	}

	// nullptrチェック
	if (m_pState != nullptr)
	{
		// 終了処理
		m_pState->OnExit();

		// ポインタの破棄
		delete m_pState;

		// null初期化
		m_pState = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}
//====================================
// 更新処理
//====================================
void CBoss::Update(void)
{
	// 死んでいたら
	if (m_isdaeth) return;

	// 減算
	DecCoolTime();

	// nullチェック
	if (m_pState != nullptr)
	{
		// ステート更新
		m_pState->Update();
	}

	// モーション全体更新
	m_pMotion->Update(m_pModel, NUMMODELS);
}
//====================================
// 描画処理
//====================================
void CBoss::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		// 全モデル描画
		m_pModel[nCnt]->Draw();
	}

	// デバッグフォント
	{
		CDebugproc::Print("ボス座標 [ %.2f ,%.2f , %.2f]", m_pos.x, m_pos.y, m_pos.z);
		CDebugproc::Draw(0, 40);

		CDebugproc::Print("ボスモーション数 { %d }", m_type);
		CDebugproc::Draw(0, 180);

		CDebugproc::Print("ボス右手座標 { %.2f,%.2f,%.2f }", GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._41, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._42, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._43);
		CDebugproc::Draw(0, 300);

		CDebugproc::Print("ボス体力 { %d }", m_pParam->GetHp());
		CDebugproc::Draw(0, 400);

		CDebugproc::Print("ボスクールタイム { %d }",m_nCoolTime);
		CDebugproc::Draw(1080, 400);

		// デバッグフォント
		m_pMotion->Debug();
	}
}
//====================================
// 右手とプレイヤーの当たり判定
//====================================
bool CBoss::CollisionRightHand(D3DXVECTOR3* pPos)
{
	// 生成フラグを作成
	static bool isCreate = false;

	// 一定フレーム内
	if (m_pMotion->CheckFrame(30, 30, PATTERN_HAND) && !isCreate)
	{
		// 攻撃サインを生成
		CAttackSign::Create(50.0f, 50.0f);

		// 生成フラグを有効化
		isCreate = true;
	}
	else
	{
		// フレーム外ならリセット
		isCreate = false;
	}

	// 一定フレーム内
	if (m_pMotion->CheckFrame(100, 140, PATTERN_HAND) && m_isdaeth == false)
	{
		// モデルのパーツ取得
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // 右手

		// nullだったら
		if (!pRightHand) return false;

		// 右手のワールドマトリックスを取得
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// 差分計算
		D3DXVECTOR3 diff = *pPos - D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// 計算した差分の長さ取得
		float fDist = D3DXVec3Length(&diff);

		// 距離を返す
		return fDist <= (HITRANGE * HITRANGE);
	}
	else
	{
		// 当たらないとき
		return false;
	}
}
//====================================
// インパクトモーション時の当たり判定
//====================================
bool CBoss::CollisionImpactScal(D3DXVECTOR3* pPos)
{
	// モデルのパーツ取得
	CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // 右手

	// nullだったら
	if (!pRightHand) return false;

	// モデルのパーツ取得
	CModel* pLeftHand = GetModelPartType(CModel::PARTTYPE_LEFT_HAND); // 左手

	// nullだったら
	if (!pLeftHand) return false;

	// モデルのパーツ取得
	CModel* pHead = GetModelPartType(CModel::PARTTYPE_HEAD); // 頭

	// nullだったら
	if (!pHead) return false;

	// 手のワールドマトリックスを取得
	D3DXMATRIX mtxRight = pRightHand->GetMtxWorld();
	D3DXMATRIX mtxLeft = pLeftHand->GetMtxWorld();

	// 頭のワールドマトリックス
	D3DXMATRIX mtxHead = pHead->GetMtxWorld();

	// 生成フラグを作成
	static bool isCreate = false;

	// 一定フレーム内
	if (m_pMotion->CheckFrame(60, 60, PATTERN_IMPACT) && !isCreate)
	{
		// 攻撃サインを生成
		CAttackSign::Create(50.0f, 50.0f);

		// 生成フラグを有効化
		isCreate = true;
	}
	else
	{
		// フレーム外ならリセット
		isCreate = false;
	}

	// 一定フレーム内
	if (m_pMotion->CheckFrame(120, 160, PATTERN_IMPACT) && m_isdaeth == false)
	{
		// 座標を格納
		D3DXVECTOR3 posRight(mtxRight._41, mtxRight._42, mtxRight._43);
		D3DXVECTOR3 posLeft(mtxLeft._41, mtxLeft._42, mtxLeft._43);

		// 両手の座標の中心点を計算
		D3DXVECTOR3 HandCenterPos = (posRight + posLeft) * 0.5f;

		// プレイヤーとの距離を測定
		const float fHitRadius = 25.0f * HITRANGE; // 判定半径

		// 差分計算用
		D3DXVECTOR3 diff = VECTOR3_NULL;

		// 右手との差分
		diff = posRight - *pPos;

		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			return true;
		}

		// 左手との差分
		diff = posLeft - *pPos;

		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			return true;
		}
	}

	return false;
}

//====================================
// ヒット処理
//====================================
void CBoss::Hit(int nDamage)
{
	// フラグが立っていたら
	if (m_isdaeth) return;

	// 体力を取得
	int nHp = m_pParam->GetHp();

	// 現在体力を減らす
	nHp -= nDamage;

	if (nHp <= 0)
	{
		// 死亡判定
		m_isdaeth = true;

		// ボスを破棄
		Uninit();

		// TODO : ここに死亡モーション設定に変更
		// m_pMotion->SetMotion(CBoss::PATTERN_DEATH);
	}
	else
	{
		// セットする
		m_pParam->SetHp(nHp);
	}
}
//====================================
// 状態変更処理
//====================================
void CBoss::ChangeState(CBossStateBace* pNewState, int Id)
{
	// 自分自身をセットする
	pNewState->SetOwner(this);

	// 状態を変更する
	m_pState->ChangeState(pNewState);
}
//====================================
// 向きを回転させる処理
//====================================
void CBoss::RollToPlayer(void)
{
	// プレイヤーの取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);

	// nullなら
	if (pPlayer == nullptr) return;

	// プレイヤーの座標を取得
	D3DXVECTOR3 pPos = pPlayer->GetPos();

	// ボスからプレイヤーに一本のベクトルを生成する
	D3DXVECTOR3 VecPlayer = m_pos - pPos;

	// 水平方向の角度(Yaw)だけ求める
	float angle = atan2f(VecPlayer.x, VecPlayer.z);

	// 計算した角度をセット
	m_rot.y = angle;
}
