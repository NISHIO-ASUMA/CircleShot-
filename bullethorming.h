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

	CBulletHorming();
	~CBulletHorming();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBulletHorming* Create(const char * pFileNama,D3DXVECTOR3 pos);

	bool Collision(D3DXVECTOR3 DestPos);


private:
	float m_fRange;		// 追従距離計算用
	bool m_isHit;		// 当たり判定フラグ

};

#endif
