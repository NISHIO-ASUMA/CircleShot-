//====================================
//
// 弾の処理 [ bullet.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "bullet.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"
#include "effect.h"
#include "boss.h"
#include "particle.h"
#include "gamemanager.h"
#include "effectlaser.h"
#include "charge.h"

//*****************************
// 静的メンバ変数宣言
//*****************************
CBullet::BTYPE CBullet::m_Type = CBullet::BTYPE_NONE; // 種類

//*******************************
// 定数宣言
//*******************************
namespace BULLETINFO
{
	constexpr int BULLET_DAMAGE = 1;		// 弾のダメージ
	constexpr int ACTIVEEFFECTNUM = 3;		// 出現エフェクト制限数
	constexpr int LASER_DAMAGE = 3;			// レーザー弾のダメージ

	constexpr float BULLET_SIZE = 30.0f;	// 弾のサイズ
	constexpr float BULLET_LASER = 30.0f;   // レーザー幅
	constexpr float BULLET_NORMAL = 10.0f;	// 通常弾の幅
	constexpr float BULLET_SPEED = 15.0f;	// 進む速度

	const D3DXVECTOR3 DestPos = { 0.0f,10.0f,0.0f };	// エフェクト出現座標
}

//===============================
// オーバーロードコンストラクタ
//===============================
CBullet::CBullet(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_nLife = NULL;
	m_nIdxTexture = NULL;
	m_move = VECTOR3_NULL;
	m_OldPos = VECTOR3_NULL;
}
//===============================
// デストラクタ
//===============================
CBullet::~CBullet()
{
	// 無し
}
//===============================
// 弾の生成
//===============================
CBullet* CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, BTYPE nType, const float fWidth, const float fHeight,const int nLife)
{
	// 弾のインスタンス生成
	CBullet* pBullet = new CBullet;

	// インスタンスの生成に失敗したら
	if (pBullet == nullptr) return nullptr;

	// オブジェクト設定
	pBullet->SetTexture(nType);
	pBullet->SetPos(pos);
	pBullet->SetType(nType);
	pBullet->SetSize(fWidth, fHeight);
	pBullet->m_nLife = nLife;

	// 初期化に失敗したら
	if (FAILED(pBullet->Init(rot)))
	{
		// nullptrを返す
		return nullptr;
	}

	// 生成されたポインタを返す
	return pBullet;
}
//===============================
// 弾の種類セット
//===============================
void CBullet::SetType(BTYPE type)
{
	// 種類設定
	m_Type = type;
}
//===============================
// 種類ごとのテクスチャセット
//===============================
void CBullet::SetTexture(BTYPE type)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ設定
	switch (type)
	{
	case BTYPE_PLAYER:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\bullet002.png");
		break;

	default:
		break;
	}
}
//===============================
// 弾の初期化
//===============================
HRESULT CBullet::Init(D3DXVECTOR3 rot)
{
	// 親クラスの初期化
	CBillboard::Init();

	// オブジェクトの種類を設定する
	SetObjType(TYPE_BULLET);

	// 移動量を計算
	m_move = D3DXVECTOR3(rot.x * BULLETINFO::BULLET_SPEED, rot.y,rot.z * BULLETINFO::BULLET_SPEED);

	return S_OK;
}
//===============================
// 弾の終了
//===============================
void CBullet::Uninit(void)
{
	// 親クラスの破棄
	CBillboard::Uninit();
}
//===============================
// 弾の更新
//===============================
void CBullet::Update(void)
{
	// 弾の座標を取得
	D3DXVECTOR3 BulletPos = GetPos();

	// 寿命を徐々に減らす
	m_nLife--;
	
	// 過去の座標を保持する
	m_OldPos = BulletPos;

	for (int nCnt = 0; nCnt < BULLETINFO::ACTIVEEFFECTNUM; nCnt++)
	{
		// 長さ
		D3DXVECTOR3 VecMove = m_OldPos - BulletPos;

		// 割合
		float fRate = static_cast<float>(nCnt) / BULLETINFO::ACTIVEEFFECTNUM;

		// 最終移動量
		D3DXVECTOR3 DestMove = m_OldPos + VecMove * fRate;

		switch (m_Type)
		{
		case BTYPE_PLAYER:
			// 通常エフェクト
			CEffect::Create(DestMove, COLOR_PURPLE, VECTOR3_NULL, m_nLife, BULLETINFO::BULLET_NORMAL);
			break;

		case BTYPE::BTYPE_LASER:
			// レーザーエフェクト生成
			 CEffectLaser::Create(DestMove, BULLETINFO::DestPos, LASER, VECTOR3_NULL, m_nLife, BULLETINFO::BULLET_LASER);
			break;

		default:
			break;
		}

	}

	// 位置を更新
	BulletPos += m_move;

	// 座標を更新
	SetPos(BulletPos);

	// 敵との当たり判定
	bool isHit = Collision(BulletPos);

	// 体力が0以下 かつ 敵に当たっていなかったら
	if (m_nLife <= 0 && !isHit)
	{
		// 未使用状態
		Uninit();
	}
}
//===============================
// 弾の描画
//===============================
void CBullet::Draw(void)
{
#ifdef _DEBUG
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ読み込み
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// オブジェクトの描画
	CBillboard::Draw();
#endif
}
//====================================
// 当たり判定処理 ( 引数 : 弾の座標 )
//====================================
bool CBullet::Collision(D3DXVECTOR3 pos)
{
	// ボス取得
	CBoss* pBoss = CGameManager::GetBoss();

	if (pBoss != nullptr)
	{
		// プレイヤーの弾
		if (GetType() == BTYPE_PLAYER)
		{
			// ボスの座標,サイズ取得
			D3DXVECTOR3 BossPos = pBoss->GetPos();
			float fBossSize = pBoss->GetSize();

			// 
			D3DXVECTOR3 testPos = pos;
			testPos.y = BossPos.y; 

			D3DXVECTOR3 diff = BossPos - testPos;
			float fDistanceSq = D3DXVec3LengthSq(&diff);

			// ボスと弾の半径の合計
			float fBulletRadius = BULLETINFO::BULLET_SIZE;
			float fHitRadius = fBossSize + fBulletRadius;
			float fLength = fHitRadius * fHitRadius;

			if (fDistanceSq <= fLength)
			{
				// パーティクル生成
				CParticle::Create(D3DXVECTOR3(BossPos.x, 30.0f, BossPos.z),
					COLOR_RED,
					35, 150, 100, 300);

				// 弾の座標を渡す
				pBoss->Hit(BULLETINFO::BULLET_DAMAGE, pos);

				// 弾を消す
				CBullet::Uninit();

				// ゲージ値を加算する
				CCharge::AddCharge(0.3f);

				// 当たった判定を返す
				return true;
			}
		}

		// レーザー弾
		if (GetType() == BTYPE_LASER)
		{
			// ボスの座標,サイズ取得
			D3DXVECTOR3 BossPos = pBoss->GetPos();
			float fBossSize = pBoss->GetSize();

			// 座標を設定
			D3DXVECTOR3 TargetPos = pos;
			TargetPos.y = BossPos.y;

			// 差分を計算
			D3DXVECTOR3 diff = BossPos - TargetPos;

			// 差分の長さを取得
			float fDistanceSq = D3DXVec3LengthSq(&diff);

			// ボスと弾の半径の合計
			float fBulletRadius = BULLETINFO::BULLET_SIZE;
			float fHitRadius = fBossSize + fBulletRadius;
			float fLength = fHitRadius * fHitRadius;

			// 距離が長さ以下なら
			if (fDistanceSq <= fLength)
			{
				// 弾の座標を渡す
				pBoss->Hit(BULLETINFO::LASER_DAMAGE, pos);

				// 弾を消す
				CBullet::Uninit();

				// ゲージ値を加算する
				CCharge::AddCharge(0.2f);

				// 当たった判定を返す
				return true;
			}
		}
	}

	// 通常時
	return false;
}
