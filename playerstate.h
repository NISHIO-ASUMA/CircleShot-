//============================================
//
// プレイヤー状態管理処理 [ playerstate.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _PLAYERSTATE_H_ // このマクロ定義がされてなかったら
#define _PLAYERSTATE_H_ // 2重インクルード防止のマクロ定義

//**************************
// インクルードファイル宣言
//**************************
#include "state.h"
#include "player.h"

//*********************************
// プレイヤーのベース状態管理
//*********************************
class CPlayerStateBase : public CStateBase
{
public:

	//***************************
	// 状態管理ID列挙型
	//***************************
	enum ID
	{
		ID_NEUTRAL, // 待機
		ID_MOVE, // 移動
		ID_ACTION, // 攻撃
		ID_JUMP, // ジャンプ
		ID_AVOID, // 回避
		ID_DAMAGE,// ダメージ
		ID_MAX
	};

	CPlayerStateBase();
	~CPlayerStateBase();

	void SetOwner(CPlayer* pPlayer) { m_pPlayer = pPlayer; } // ポインタセット

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
	CPlayer* m_pPlayer;		// プレイヤーのポインタ

private:
	ID m_ID;		// 列挙型のポインタ
};

//*********************************
// 待機状態時の状態管理
//*********************************
class CPlayerStateNeutral : public CPlayerStateBase
{
public:
	CPlayerStateNeutral();
	~CPlayerStateNeutral();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();
};

//*********************************
// 移動時の状態管理
//*********************************
class CPlayerStateMove : public CPlayerStateBase
{
public:
	CPlayerStateMove();
	~CPlayerStateMove();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();
};

//*********************************
// 攻撃時の状態管理
//*********************************
class CPlayerStateAction : public CPlayerStateBase
{
public:
	CPlayerStateAction();
	~CPlayerStateAction();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();
};

//*********************************
// ダメージ状態時の管理
//*********************************
class CPlayerStateDamage : public CPlayerStateBase
{
public:

	//**************************
	// 状態列挙型
	//**************************
	enum DAMAGESTATE
	{
		DAMAGESTATE_NONE,
		DAMAGESTATE_NORMAL,
		DAMAGESTATE_DAMAGE,
		DAMAGESTATE_INVINCIBLE,
		DAMAGESTATE_MAX
	};

	CPlayerStateDamage(int nDamage);
	~CPlayerStateDamage();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

private:
	int m_nStateCount;	// 管理カウント
	int m_nDamage;// ダメージ数
	int m_nCurrentstate;	// 現在状態
};

//*********************************
// ジャンプ状態時の管理
//*********************************
class CPlayerStateJump : public CPlayerStateBase
{
public:

	CPlayerStateJump();
	~CPlayerStateJump();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

private:
};

#endif