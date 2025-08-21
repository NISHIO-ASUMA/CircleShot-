//====================================
//
// 敵の状態管理処理 [ enemystate.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _ENEMYSTATE_H_ // このマクロ定義がされてなかったら
#define _ENEMYSTATE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "state.h"
#include "enemy.h"

//**************************
// 敵の状態管理基底クラス
//**************************
class CEnemyStateBase :public CStateBase
{
public:
	//***************************
	// 状態管理ID列挙型
	//***************************
	enum ID
	{
		ID_NONE, // 設定なし
		ID_FALL, // 落下状態
		ID_MOVE, // 移動
		ID_DEATH,// 死亡
		ID_MAX
	};

	CEnemyStateBase();
	~CEnemyStateBase();

	void SetOwner(CEnemy* pEnemy) { m_pEnemy = pEnemy; } // ポインタセット

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
	CEnemy* m_pEnemy;	// 敵のポインタ

private:
	ID m_ID;		// 列挙型のメンバ変数
};

//**************************
// 落下状態時の管理
//**************************
class CEnemyStateFall : public CEnemyStateBase
{
public:
	CEnemyStateFall();
	~CEnemyStateFall();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

private:
	float m_fSpeedFall;	// 落下スピード
};

//**************************
// 移動状態時の管理
//**************************
class CEnemyStateMove : public CEnemyStateBase
{
public:
	CEnemyStateMove();
	~CEnemyStateMove();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();
};
#endif
