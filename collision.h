//=============================================
//
// 当たり判定の管理を行う [ collision.h ]
// Author: Asuma Nishio
// 
//==============================================

#ifndef _COLLISION_H_ // このマクロ定義がされてなかったら
#define _COLLISION_H_ // 2重インクルード防止のマクロ定義

//************************************
// コリジョンクラスを定義
//************************************
class CCollision
{
public:
	CCollision();
	~CCollision();

	D3DXVECTOR3 CollisionSphere(D3DXVECTOR3* outPos, D3DXVECTOR3* pPos, D3DXVECTOR3* pPos1, float CollsionSize);

private:

};

#endif // !_COLLISION_H_






