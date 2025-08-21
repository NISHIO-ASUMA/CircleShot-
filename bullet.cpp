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

//*******************************
// 定数宣言
//*******************************
namespace BulletConst
{
	constexpr float  BULLET_SIZE = 30.0f;	// 弾のサイズ
	constexpr int  BULLET_DAMAGE = 1;		// 弾のダメージ
}

//===============================
// オーバーロードコンストラクタ
//===============================
CBullet::CBullet(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_nLife = NULL;
	m_move = VECTOR3_NULL;
	m_Type = BTYPE_NONE;
	m_nIdxTexture = NULL;
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
	// 最大数
	int nNum = CObject::GetNumAll();

	// 最大数超えたら
	if (nNum >= MAX_OBJECT -1)
	{
		// nullを返す
		return nullptr;
	}

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

	case BTYPE_ENEMY:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\gold.jpg");
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
	m_move = D3DXVECTOR3(rot.x * 15.0f, rot.y,rot.z * 15.0f);

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

	// カラーセット
	SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

	// エフェクト生成
	CEffect::Create(BulletPos, D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), VECTOR3_NULL, m_nLife, 10.0f);

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
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ読み込み
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// オブジェクトの描画
	CBillboard::Draw();
}
//====================================
// 当たり判定処理 ( 引数 : 弾の座標 )
//====================================
bool CBullet::Collision(D3DXVECTOR3 pos)
{
	// ボス取得
	CBoss* pBoss = CGameManager::GetBoss();

	// オブジェクトが取得できたら
	if (pBoss != nullptr)
	{
		// 弾の種類を取得
		BTYPE Type = GetType();

		if (Type == BTYPE_PLAYER)
		{
			// ボスの座標,サイズ取得
			D3DXVECTOR3 BossPos = pBoss->GetPos();
			float fBossSize = pBoss->GetSize();

			// 弾の座標のYをボスのYに合わせる
			pos.y = BossPos.y;

			// XZ平面上の距離を計算
			D3DXVECTOR3 diff = BossPos - pos;

			float fDistanceSq = D3DXVec3LengthSq(&diff);

			// ボスと弾の半径の合計
			float fBulletRadius = BulletConst::BULLET_SIZE;

			// ヒットの半径を計算
			float fHitRadius = fBossSize + fBulletRadius;

			// 判定の範囲を計算
			float fLength = fHitRadius * fHitRadius;

			// 範囲内なら
			if (fDistanceSq <= fLength)
			{
				// テストでパーティクル生成
				CParticle::Create(D3DXVECTOR3 (BossPos.x,30.0f,BossPos.z), D3DXCOLOR(1.0f,0.0f,0.0f,1.0f), 35, 150, 100, 300);

				// ボスにダメージ
				pBoss->Hit(3);

				// 弾を消す
				CBullet::Uninit();

				// 当たった判定を返す
				return true;
			}
		}
	}

	// 当たらないとき
	return false;
}
