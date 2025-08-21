//============================================
//
// 状態管理処理 [ state.cpp ]
// Author: Asuma Nishio
//
//=============================================

//***********************
// インクルードファイル
//***********************
#include "state.h"
#include "playerstate.h"

//**********************
// 定数宣言
//**********************
constexpr int  MAX_STATECOUNT = 40; // 最大継続時間

//==================================
// ステートベースコンストラクタ
//==================================
CStateBase::CStateBase()
{
	// 無し
}
//==================================
// ステートベースデストラクタ
//==================================
CStateBase::~CStateBase()
{
	// 無し
}


//==================================
// ステートマシンコンストラクタ
//==================================
CStateMachine::CStateMachine()
{
	// 値のクリア
	m_pNowState = nullptr;
}
//==================================
// ステートマシンデストラクタ
//==================================
CStateMachine::~CStateMachine()
{
	// 無し
}
//==================================
// ステートマシン更新処理
//==================================
void CStateMachine::Update(void)
{
	// nullptrじゃなかったら
	if (m_pNowState != nullptr)
	{
		// 更新開始
		m_pNowState->OnUpdate();
	}
}
//==================================
// ステート変更処理
//==================================
void CStateMachine::ChangeState(CStateBase* pNewState)
{	
	// ポインタが存在するとき
	if (m_pNowState != nullptr && pNewState != nullptr)
	{
		// ID が同じなら
		if (m_pNowState->GetID() == pNewState->GetID())
		{
			delete pNewState;

			// ここで処理を返す
			return;
		}
	}

	// すでにステートがセットされてたら終了する
	if (m_pNowState != nullptr)
	{
		// 終了
		m_pNowState->OnExit();

		// ポインタの破棄
		delete m_pNowState;

		// nullptrに初期化する
		m_pNowState = nullptr;
	}

	// 新しいステートをセットする
	m_pNowState = pNewState;

	// 新しいステートを開始する
	m_pNowState->OnStart();
}
//==================================
// ステート終了処理
//==================================
void CStateMachine::OnExit()
{
	// すでにステートがセットされてたら終了する
	if (m_pNowState != nullptr)
	{
		// 破棄
		delete m_pNowState;

		// null初期化
		m_pNowState = nullptr;
	}
}
//==================================
// 現在状態を取得
//==================================
int CStateMachine::GetNowStateID()
{
	if (m_pNowState)
		return m_pNowState->GetID(); // 仮想関数として

	return 0; // ニュートラル
}