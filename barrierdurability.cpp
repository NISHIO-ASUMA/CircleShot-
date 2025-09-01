//===============================================
//
// シールド関数 [ barrierdurability.cpp ]
// Author : Asuma Nishio
//
//===============================================

//*********************************
// インクルードファイル
//*********************************
#include "barrierdurability.h"
#include "manager.h"
#include "texture.h"
#include "template.h"
#include "player.h"
#include "gamemanager.h"
#include "particle.h"

//*********************************
// 名前空間
//*********************************
namespace BARRIERINFO
{
	constexpr float COLLISIOLANGE = 100.0f; // コリジョンサイズ
	constexpr float VALUEROT = 0.03f;	// 加算角度
	constexpr float DISTANCE = 50.0f;	// 距離
};

//=======================================
// オーバーロードコンストラクタ
//=======================================
CBarrierDurability::CBarrierDurability(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_nIdx = NULL;
}
//=======================================
// デストラクタ
//=======================================
CBarrierDurability::~CBarrierDurability()
{
	// 無し
}
//=======================================
// 生成処理
//=======================================
CBarrierDurability* CBarrierDurability::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char * pFilename)
{
	// インスタンス生成
	CBarrierDurability* pbarrier = new CBarrierDurability;

	// nullなら
	if (pbarrier == nullptr) return nullptr;

	// オブジェクト設定
	pbarrier->SetFilePass(pFilename);
	pbarrier->SetPos(pos);
	pbarrier->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pbarrier->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pbarrier;
}
//=======================================
// 初期化処理
//=======================================
HRESULT CBarrierDurability::Init(void)
{
	// 親クラスの初期化処理
	CObjectX::Init();

	// オブジェクトの種類を設定
	SetObjType(CObject::TYPE_BARRIER);

	// 初期化結果を返す
	return S_OK;
}
//=======================================
// 終了処理
//=======================================
void CBarrierDurability::Uninit(void)
{
	// 親クラスの終了処理
	CObjectX::Uninit();
}
//=========================================
// 更新処理
//=========================================
void CBarrierDurability::Update(void)
{
	// プレイヤーを取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (!pPlayer) return;

	// 回転角度を更新
	static float fValueAngle = NULL;

	fValueAngle += BARRIERINFO::VALUEROT;

	// 距離を計算
	float fDistance = BARRIERINFO::DISTANCE;
	float DestPosY = pPlayer->GetPos().y + BARRIERINFO::DISTANCE;

	// バリアごとの角度オフセット
	float angleOffset = (2.0f * D3DX_PI / CGameManager::GetBarrier()->GetNumBarrier()) * m_nIdx;
	float currentAngle = fValueAngle + angleOffset;

	// 座標を計算
	float DestPosX = pPlayer->GetPos().x + cosf(currentAngle) * fDistance;
	float DestPosZ = pPlayer->GetPos().z + sinf(currentAngle) * fDistance;

	// オブジェクトの座標にセット
	SetPos(D3DXVECTOR3(DestPosX, DestPosY, DestPosZ));

	// オブジェクトの内側をプレイヤー方向を向かせる
	D3DXVECTOR3 VecToPlayer = pPlayer->GetPos() - CObjectX::GetPos();
	float fAngleY = atan2f(VecToPlayer.x, VecToPlayer.z);

	// 現在角度を取得
	D3DXVECTOR3 rot = GetRot();

	// 正規化
	rot.y = NormalAngle(fAngleY);

	// オブジェクトの角度にセット
	SetRot(rot);
}
//=======================================
// 描画処理
//=======================================
void CBarrierDurability::Draw(void)
{
	// 親クラスの描画
	CObjectX::Draw();
}

//=======================================
// バリアオブジェクトの当たり判定関数
//=======================================
bool CBarrierDurability::Collision(D3DXVECTOR3* DestPos)
{
	// 現在座標を取得
	D3DXVECTOR3 NowPos = GetPos();

	// コリジョンする線分の長さを計算
	D3DXVECTOR3 CollisionPos = NowPos - *DestPos;

	// 線分の長さを算出
	float fRange = D3DXVec3Length(&CollisionPos);

	// ヒット半径よりも小さい値になったら
	if (fRange <= BARRIERINFO::COLLISIOLANGE)
	{
		// サウンドのポインタを取得
		CSound* pSound = CManager::GetSound();

		// nullチェック
		if (pSound != nullptr)
		{
			// サウンド再生
			pSound->PlaySound(CSound::SOUND_LABEL_ITEM);
		}

		// バリアマネージャを取得
		CBarrierManager* pBarrierMgr = CGameManager::GetBarrier();

		// nullじゃなかったら
		if (pBarrierMgr != nullptr)
		{
			// バリア減算
			pBarrierMgr->DamageBarrier(1);

			// パーティクル生成
			CParticle::Create(D3DXVECTOR3(DestPos->x, 20.0f, DestPos->z),COLOR_GREEN, 100, 100, 200, 100);
		}

		// ヒット判定を返す
		return true;
	}

	// 当たってないとき
	return false;
}