//=============================================
//
// 当たり判定の管理を行う [ collision.h ]
// Author: Asuma Nishio
// 
//==============================================

//*****************************
// インクルードファイル
//*****************************
#include "collision.h"

//==============================================
// コンストラクタ
//==============================================
CCollision::CCollision()
{
	// ない
}
//==============================================
// デストラクタ
//==============================================
CCollision::~CCollision()
{
	// 無し
}
//==============================================
// 球形当たり判定
//==============================================
bool CCollision::CollisionSphere(D3DXVECTOR3* pPos, D3DXVECTOR3* pDestPos,const float fMyRadius,const float fHitRadius)
{
	// 距離の差分を計算する
	float fDisX = pDestPos->x - pPos->x;
	float fDisY = pDestPos->y - pPos->y;
	float fDisZ = pDestPos->z - pPos->z;

	// 半径のサイズを計算
	float fRadX = fMyRadius + fHitRadius;
	float fRadY = fMyRadius + fHitRadius;
	float fRadZ = fMyRadius + fHitRadius;

	// 総数を計算する
	float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
	float fRadAll = (fRadX + fRadY + fRadZ) * (fRadX + fRadY + fRadZ);

	// 半径内に入っていたら
	if (fDissAll <= fRadAll)
	{
		// コリジョン判定を返す
		return true;
	}

	// 範囲外で当たっていないとき
	return false;
}
