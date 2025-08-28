//===================================================
//
// 弾のオブジェクトホーミング処理 [ bullethorming.h ]
// Author: Asuma Nishio
//
//===================================================

#ifndef _BULLETHORMING_H_ // このマクロ定義がされてなかったら
#define _BULLETHORMING_H_ // 2重インクルード防止のマクロ定義

//**************************
// インクルードファイル宣言
//**************************
#include "objectX.h"

//**************************
// 前方宣言
//**************************
class CObject;

//********************************
// 弾のホーミングクラスを定義
//********************************
class CBulletHorming : public CObjectX
{
public:

	//*************************
	// ホーミングの種類列挙型
	//*************************
	enum HORMING
	{
		HORMING_PLAYER, // プレイヤー追従
		HORMING_GROUND, // 地面に着弾する
		HORMING_MAX
	};

	// コンストラクタ・デストラクタ
	CBulletHorming(int nPriority = static_cast<int>(CObject::PRIORITY::BULLET));
	~CBulletHorming();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CollisionAll(void);
	bool Collision(D3DXVECTOR3 DestPos);

	// 静的メンバ関数
	static CBulletHorming* Create(const char * pFileNama,D3DXVECTOR3 pos);

private:

	float m_fRange;		// 追従距離計算用
	bool m_isHit;		// 当たり判定フラグ
};

#endif
