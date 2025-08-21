//=============================================
//
// ボスの攻撃状態管理処理 [bossattackstate.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _BOSSATTACKSTATE_H_ // このマクロ定義がされてなかったら
#define _BOSSATTACKSTATE_H_ // 2重インクルード防止のマクロ定義

//**************************
// インクルードファイル宣言
//**************************
#include "bossstate.h"

//********************************
// 殴り攻撃状態管理クラスを定義
//********************************
class CBosshandAttack : public CBossStateBace
{
public:
	CBosshandAttack();
	~CBosshandAttack();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart(void);

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate(void);

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit(void);

private:

};

//************************************
// 叩きつけ攻撃状態管理クラスを定義
//************************************
class CBossimpactAttack : public CBossStateBace
{
public:
	CBossimpactAttack();
	~CBossimpactAttack();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart(void);

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate(void);

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit(void);

private:

};

//************************************
// 振り回し攻撃状態管理クラスを定義
//************************************
class CBosscircleAttack : public CBossStateBace
{
public:
	CBosscircleAttack();
	~CBosscircleAttack();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart(void);

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate(void);

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit(void);

private:

};

#endif
