//====================================
//
// 敵の処理 [ enemy.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "enemy.h"
#include "gamemanager.h"
#include "debugproc.h"
#include "parameter.h"
#include "particle.h"
#include "state.h"
#include "enemystate.h"
#include "player.h"

//***********************************
// 静的メンバ変数宣言
//***********************************
int CEnemy::m_NumEnemy = NULL;			// 敵の総数

//===============================
// オーバーロードコンストラクタ
//===============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_move = VECTOR3_NULL;
	m_StateCount = NULL;
	m_State = ENEMYSTATE_NONE;
	m_nMoveCount = NULL;
	m_pParam = nullptr;
	m_pStateMachine = nullptr;

	m_mtxRot = {};
	m_VecAxis = VECTOR3_NULL;
	m_quat = {};
	m_fValueRot = 0.009f;

	m_fAngle = NULL;
	m_fRadius = NULL;
}
//===============================
// デストラクタ
//===============================
CEnemy::~CEnemy()
{
	// 無し
}
//===============================
// 敵の生成
//===============================
CEnemy* CEnemy::Create(const char* pFileName,const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,TYPE nType,int nHp)
{
	// 敵のインスタンス生成
	CEnemy* pEnemy = new CEnemy;

	// nullptrだったら
	if (pEnemy == nullptr) return nullptr;

	// Xファイル設定
	pEnemy->SetFilePass(pFileName);
	pEnemy->SetRot(rot);
	pEnemy->SetPos(pos);

	// 初期化に失敗したら
	if (FAILED(pEnemy->Init()))
	{
		// nullptrを返す
		return nullptr;
	}

	// 敵の種類セット
	pEnemy->SetType(nType);

	// nullじゃなかったら
	if (pEnemy->m_pParam != nullptr)
	{
		// パラメーターをセット
		pEnemy->m_pParam->SetHp(nHp);
	}

	// 敵数カウントをインクリメント
	m_NumEnemy++;

	// ポインタを返す
	return pEnemy;
}
//===============================
// 敵の初期化処理
//===============================
HRESULT CEnemy::Init(void)
{
	// 親クラスの初期化
	CObjectX::Init();

	// メンバ変数の初期化
	m_State = ENEMYSTATE_NORMAL;

	// nullだったら
	if (m_pParam == nullptr)
	{
		// パラメーターポインタを生成
		m_pParam = new CParameter;
	}

	// nullだったら
	if (m_pStateMachine == nullptr)
	{
		// ステートマシンのポインタ生成
		m_pStateMachine = new CStateMachine;

		// 初期状態をセット
		ChangeState(new CEnemyStateFall, CEnemyStateBase::ID_FALL);
	}

	// オブジェクトの種類
	SetObjType(TYPE_ENEMY);

	// クォータニオン適用
	SetUseQuat(true);

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 敵の終了処理
//===============================
void CEnemy::Uninit(void)
{
	// nullptrチェック
	if (m_pParam != nullptr)
	{
		// ポインタの破棄
		delete m_pParam;

		// nullptr代入
		m_pParam = nullptr;
	}

	// nullptrチェック
	if (m_pStateMachine != nullptr)
	{
		// 終了処理
		m_pStateMachine->OnExit();

		// ポインタの破棄
		delete m_pStateMachine;

		// nullptrにする
		m_pStateMachine = nullptr;
	}

	// オブジェクトの破棄
	CObjectX::Uninit();

	// デクリメント
	m_NumEnemy--;
}
//===========================================
// 敵の更新処理 ( 円柱の外側を回るイメージ )
//===========================================
void CEnemy::Update(void)
{
	// モデル中心座標の設定
	D3DXVECTOR3 Pos = VECTOR3_NULL;

	// 回転量を加算
	m_fValueRot += 0.03f;

	m_fRadius = CGameManager::GetCylinder()->GetRadius();
	float fLength = D3DX_PI * 2.0f * 30.0f;

	// 位置を計算
	float posx = Pos.x + cosf(m_fValueRot) * m_fRadius;
	float posz = Pos.z + sinf(m_fValueRot) * m_fRadius;
	float posy = GetPos().y; // 固定の高さ

	// 位置の更新
	SetPos(D3DXVECTOR3(posx, posy, posz));

	// 回転軸を計算する
	m_VecAxis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	

#if 0
	// 状態の更新
	m_pStateMachine->Update();
#endif
}
//===========================================
// 敵の描画処理 ( クォータニオンを適用する )
//===========================================
void CEnemy::Draw(void)
{
	// クォータニオンを生成
	D3DXQuaternionRotationAxis(&m_quat, &m_VecAxis, m_fValueRot);

	// 回転マトリックスを生成
	D3DXMatrixRotationQuaternion(&m_mtxRot, &m_quat);

	// ワールドマトリックスの取得
	D3DXMATRIX mtx = GetMtxWorld();

	// 向きを反映
	D3DXMatrixMultiply(&mtx, &m_mtxRot, &mtx);

	// セットする
	SetMtxWorld(mtx);

	// オブジェクト描画
	CObjectX::Draw();

	// デバッグ表示
	CDebugproc::Print("[ 敵の位置 : %.2f,%.2f,%.2f ]", GetPos().x, GetPos().y, GetPos().z);
	CDebugproc::Draw(0,280);
	CDebugproc::Print("[ 敵の角度 : %.2f,%.2f,%.2f ]", GetRot().x, GetRot().y, GetRot().z);
	CDebugproc::Draw(0, 260);

}
//===============================
// 敵のダメージ処理
//===============================
void CEnemy::HitEnemy(int nDamage)
{
	// パラメーター取得
	int nHp = m_pParam->GetHp();

	// 体力を減らす
	nHp -= nDamage;

	// 現在体力が0以下
	if (nHp <= NULL)
	{
		// 敵を破棄
		Uninit();

		// パーティクル生成
		CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 15.0f, GetPos().z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 100, 30, 60, 100);

		// ここで処理を返す
		return;
	}
	else
	{
		// 現在体力をセット
		m_pParam->SetHp(nHp);
	}
}
//=================================
// 敵とプレイヤーの当たり判定処理
//=================================
bool CEnemy::Collision(D3DXVECTOR3* pPos)
{// 球判定を作成する
	
	// 現在の座標を取得
	D3DXVECTOR3 EnemyPos = GetPos();

	// 当たる範囲を設定
	float HitRadius = 20.0f;
	float EHitRadius = 20.0f;

	// 2点間の距離を計算
	float fRangeX = EnemyPos.x - pPos->x;
	float fRangeY = EnemyPos.y - pPos->y;
	float fRangeZ = EnemyPos.z - pPos->z;

	// 距離の2乗を計算
	float fDis = (fRangeX * fRangeX) + (fRangeY * fRangeY) + (fRangeZ * fRangeZ);

	// 半径の距離を計算
	float fHitAll = HitRadius + EHitRadius;
	float fRadiusSum = fHitAll * fHitAll;

	// 範囲内にあるなら
	if (fDis <= fRadiusSum)
	{
		// 敵を消す
		Uninit();

		// 当たった結果を返す
		return true;
	}
	 
	// デフォルトで返す
	return false;
}
//=================================
// 状態変更処理
//=================================
void CEnemy::ChangeState(CEnemyStateBase* pNewState, int id)
{
	// セットする
	pNewState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pNewState);
}
//=================================
// 移動状態更新処理
//=================================
void CEnemy::UpdateMoving(void)
{
	// 無し
}
