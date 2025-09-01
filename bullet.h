//=====================================
//
// 弾の処理 [ bullet.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BULLET_H_ // このマクロ定義がされてなかったら
#define _BULLET_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "billboard.h"
#include "object.h"

//**************************
// 弾クラスを定義
//**************************
class CBullet : public CBillboard
{
public:
	//********************
	// 弾の種類を定義
	//********************
	enum BTYPE
	{
		BTYPE_NONE = 0,
		BTYPE_PLAYER,
		BTYPE_LASER,
		BTYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CBullet(int nPriority = static_cast<int>(CObject::PRIORITY::BULLET));
	~CBullet();

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3 pos); 

	// 静的メンバ関数
	static CBullet* Create(const D3DXVECTOR3 pos,const D3DXVECTOR3 rot,BTYPE nType,const float fWidth, const float fHeight, const int nLife);

	// セッター
	static void SetType(BTYPE type);
	void SetTexture(BTYPE type);

	// ゲッター
	static BTYPE GetType(void) { return m_Type; }

private:
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_OldPos;	// 過去の座標
	static BTYPE m_Type;	// 種類
	D3DCOLOR m_col;			// 弾のカラー
	int m_nIdxTexture;		// テクスチャインデックス
	int m_nLife;			// 体力
};
#endif
