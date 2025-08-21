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

//*******************************
// コンストラクタ
//*******************************
CCollision::CCollision()
{
    // ない
}
//*******************************
// デストラクタ
//*******************************
CCollision::~CCollision()
{
    // 無し
}
//*******************************
// 球形当たり判定
//*******************************
D3DXVECTOR3 CCollision::CollisionSphere(D3DXVECTOR3* outPos, D3DXVECTOR3* pPos, D3DXVECTOR3* pPos1,float CollsionSize)
{
    // まず,2点間のベクトルを求める
    D3DXVECTOR3 Vec = VECTOR3_NULL;

    Vec.x = pPos1->x - pPos->x;
    Vec.y = pPos1->y - pPos->y;
    Vec.z = pPos1->z - pPos->z;

    // 計算したベクトルの長さを取得する
    float fLength = D3DXVec3Length(&Vec);

    // 計算した範囲内に入っていたら
    if (fLength < CollsionSize)
    {
        // ベクトルの正規化をする
        D3DXVec3Normalize(&Vec,&Vec);
        
        // めり込み量を距離を計算する
        float fDestLength = CollsionSize - fLength; // めり込み量

        // 出力する座標を計算する
        outPos->x = pPos1->x + Vec.x * fDestLength;
        outPos->y = pPos1->y + Vec.y * fDestLength;
        outPos->z = pPos1->z + Vec.z * fDestLength;
    }
    else
    {
        // 当たらないときは元の位置を返す
       *outPos = *pPos;
    }

    // 押し戻した座標を返す
    return *outPos;
}
