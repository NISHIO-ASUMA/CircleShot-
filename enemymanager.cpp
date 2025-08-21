//=====================================
//
// 敵の管理を行う [ enemymanager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "enemymanager.h"
#include "input.h"
#include "debugproc.h"
#include "manager.h"

//**************************************
// コンストラクタ
//**************************************
CEnemymanager::CEnemymanager()
{
	// 値のクリア
	m_nManagEnemy = 0;
}
//**************************************
// デストラクタ
//**************************************
CEnemymanager::~CEnemymanager()
{
	// 無し
}
//**************************************
// 生成
//**************************************
void CEnemymanager::Create(void)
{
	// 敵の生成
	//CEnemy::Create(D3DXVECTOR3(500.0f,300.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),CEnemy::ENEMYTYPE_FACE);
	//CEnemy::Create(D3DXVECTOR3(800.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_GOLD);

}
//**************************************
// 終了
//**************************************
void CEnemymanager::Uninit(void)
{
	// 無し
}
//**************************************
// 更新
//**************************************
void CEnemymanager::Update(void)
{
	// キーボードへのポインタを取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	// 現在の敵の総数を取得
	m_nManagEnemy = CEnemy::GetEnemy();

	if (m_nManagEnemy <= 0 && pInput->GetTrigger(DIK_M))
	{
		//// 敵の生成
		//CEnemy::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_FACE);
		//CEnemy::Create(D3DXVECTOR3(400.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_GOLD);
		//CEnemy::Create(D3DXVECTOR3(600.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_FACE);
		//CEnemy::Create(D3DXVECTOR3(800.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_GOLD);
	}
}
//**************************************
// 描画
//**************************************
void CEnemymanager::Draw(void)
{
	// // デバッグフォントの描画
	// CDebugproc::Print("敵の数 ( %d )", m_nManagEnemy);
	// 
	// // 描画
	// CDebugproc::Draw(0, 40);
}
