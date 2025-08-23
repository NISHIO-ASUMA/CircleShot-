//===================================
//
// アイテム処理 [ item.cpp ]
// Author: Asuma Nishio
//
//===================================

//**************************
// インクルードファイル宣言
//**************************
#include "item.h"
#include "barrierdurability.h"
#include "template.h"
#include "barriermanager.h"
#include "gamemanager.h"

//**************************
// 名前空間
//**************************
namespace ITEMINFO
{
	constexpr float HITRANGE = 60.0f; // 当たり半径の範囲

	D3DXVECTOR3 PointPos[3] = // 出現座標
	{
		{},
		{},
		{}
	};
};

//=================================
// オーバーロードコンストラクタ
//=================================
CItem::CItem(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
}
//=================================
// デストラクタ
//=================================
CItem::~CItem()
{
	// 無し
}
//=================================
// 生成処理
//=================================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* Filename)
{
	// インスタンス生成
	CItem* pItem = new CItem;

	// nullなら
	if (pItem == nullptr) return nullptr;

	// オブジェクト設定
	pItem->SetFilePass(Filename);
	pItem->SetPos(pos);
	pItem->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pItem->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタ
	return pItem;
}
//=================================
// 初期化処理
//=================================
HRESULT CItem::Init(void)
{
	// 親クラスの初期化処理
	CObjectX::Init();

	// オブジェクトの種類定義
	SetObjType(TYPE_ITEM);

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CItem::Uninit(void)
{
	// 親クラスの終了処理
	CObjectX::Uninit();
}
//=================================
// 更新処理
//=================================
void CItem::Update(void)
{
	// 現在の角度を取得
	D3DXVECTOR3 rot = GetRot();

	// 回転角を加算
	rot.y += 0.03f;

	// 角度正規化関数
	rot.y = NormalAngle(rot.y);

	// 角度セット
	SetRot(rot);
}
//=================================
// 描画処理
//=================================
void CItem::Draw(void)
{
	// 親クラスの描画処理
	CObjectX::Draw();
}
//=================================
// 当たり判定処理
//=================================
bool CItem::Collision(D3DXVECTOR3* pPos)
{
	// 現在座標を取得
	D3DXVECTOR3 NowPos = GetPos();

	// コリジョンする線分の長さを計算
	D3DXVECTOR3 CollisionPos = NowPos - *pPos;

	// 線分の長さを算出
	float fRange = D3DXVec3Length(&CollisionPos);

	// ヒット半径よりも小さい値になったら
	if (fRange <= ITEMINFO::HITRANGE)
	{
		// 対象のオブジェクト消去
		Uninit();
		
		// バリアマネージャを取得して耐久値を増やす
		CBarrierManager* pBarrierMgr = CGameManager::GetBarrier();

		// nullじゃなかったら
		if (pBarrierMgr != nullptr)
		{
			// バリア加算
			pBarrierMgr->AddBarrier(1);
		}

		// ヒット判定を返す
		return true;
	}

	// 当たってないとき
	return false;
}
