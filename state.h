//============================================
//
// 状態管理処理 [ state.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _STATE_H_ // このマクロ定義がされてなかったら
#define _STATE_H_ // 2重インクルード防止のマクロ定義

//*********************************
// ステートベースクラス
//*********************************
class CStateBase
{
public:
	CStateBase();
	virtual ~CStateBase();

	// ステートが始まるときに一度だけ呼ばれる関数
	virtual void OnStart() {}

	// ステートが更新されるときに呼ばれる関数
	virtual void OnUpdate() {}

	// ステートが終了する時に一度だけ呼ばれる関数
	virtual void OnExit() {}

	// ID取得用関数
	virtual int GetID() const = 0;
};

//*********************************
// ステートマシンクラス
//*********************************
class CStateMachine
{
public:
	CStateMachine();
	~CStateMachine();

	void Update(void);						 // 更新処理
	void ChangeState(CStateBase* pNewState); // ステート変更

	void OnExit();	// 終了処理

	int GetNowStateID();

	CStateBase* GetNowState() const { return m_pNowState; }

private:
	CStateBase* m_pNowState;	// 基底クラスのステートポインタ
};

#endif
