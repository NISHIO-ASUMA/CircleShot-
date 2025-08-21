//====================================
//
// 敵の管理を行う [ enemymanager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _ENEMYMANAGER_H_ // このマクロ定義がされてなかったら
#define _ENEMYMANAGER_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "enemy.h"

//******************************
// 敵管理クラスを定義
//******************************
class CEnemymanager
{
public:
	CEnemymanager();
	~CEnemymanager();

	void Create(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	int m_nManagEnemy; // 生成敵数保存
};
#endif