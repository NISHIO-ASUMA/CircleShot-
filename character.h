//==========================================================
//
// キャラクターパラメーター設定関数 [ charactor.h ]
// Author : Asuma Nishio
//
//==========================================================

#ifndef _CHARACTER_H_ // このマクロ定義がされてなかったら
#define _CHARACTER_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2D.h"
#include "object.h"
#include "motion.h"
#include "model.h"

//*****************************
// キャラクター2Dクラスを定義
//*****************************
class CCharacter: public CObject2D
{
public:

	// キャラクター状態を設定
	enum STATE
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_INVINCIBLE,
		STATE_DAETH,
		STATE_MAX
	};

	CCharacter();
	~CCharacter();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void CharactorMove(float fMove);
	void SetLife(int nLife) { m_nLife = nLife; }
	int GetLife(void) { return m_nLife; }
	void SetAnim2D(int nMaxPattern, int nAnimCount, float TexU, float TexV);

private:
	int m_nLife;	     // 現在体力
	int m_nAnimCount2D;	 // 2Dアニメーションカウント
	int m_nAnimPattern2D; // 2Dアニメーションパターン
	int m_nMaxLife;		 // 最大体力
	float m_fMove;		// 移動量
};

//*********************************************
// キャラクター3Dクラスを定義 ( 継承 : CObject )
//*********************************************
class CCharactor3D : public CObject
{
public:
	// キャラクター状態を設定
	enum STATE
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_INVINCIBLE,
		STATE_DAETH,
		STATE_MAX
	};

	CCharactor3D(int nPriority = 4);
	~CCharactor3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	int GetLife(void)const { return m_nLife; }
	void SetLife(int nLife) { m_nLife = nLife; }

private:
	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_rotDest;	// 目的の角度
	int m_nLife;			// 現在体力	
	STATE m_state;
};
#endif
