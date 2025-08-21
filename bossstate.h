//====================================
//
// ボス状態管理処理 [ bossstate.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BOSSSTATE_H_ // このマクロ定義がされてなかったら
#define _BOSSSTATE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "state.h"
#include "boss.h"

//*****************************
// ボス状態管理親クラスを定義
//*****************************
class CBossStateBace : public CStateBase
{
public:
	//***************************
	// 状態管理ID列挙型
	//***************************
	enum ID
	{
		ID_NEUTRAL, // 待機
		ID_ACTION, // 攻撃
		ID_DAMAGE, // ダメージ
		ID_MAX
	};

	CBossStateBace();
	~CBossStateBace();

	void SetOwner(CBoss* pBoss) { m_pBoss = pBoss; } // ポインタセット

	// ステートが始まるときに一度だけ呼ばれる関数
	virtual void OnStart() {}

	// ステートが更新されるときに呼ばれる関数
	virtual void OnUpdate() {}

	// ステートが終了する時に一度だけ呼ばれる関数
	virtual void OnExit() {}

	// ゲッター
	int GetID() const override { return m_ID; }
	void SetID(ID id) { m_ID = id; }

protected:
	CBoss* m_pBoss;		// プレイヤーのポインタ

private:
	ID m_ID;		// 列挙型のポインタ
};

//*****************************
// 待機状態管理クラスを定義
//*****************************
class CBossStateNeutral : public CBossStateBace
{
public:
	CBossStateNeutral(int nTime);
	~CBossStateNeutral();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart(void);

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate(void);

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit(void);

private:
	int m_CoolTime;		// ステート切り替え時間
	int m_nCurrentState; // 現在状態
};

//*****************************
// 攻撃状態管理クラスを定義
//*****************************
class CBossStateAttack : public CBossStateBace
{
public:
	CBossStateAttack();
	~CBossStateAttack();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart(void);

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate(void);

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit(void);
};

#endif