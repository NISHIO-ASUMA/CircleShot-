//====================================
//
// リザルトシーン処理 [ result.h ]
// Author: Asuma Nishio
// 
//=====================================

#ifndef _RESULT_H_ // このマクロ定義がされてなかったら
#define _RESULT_H_ // 2重インクルード防止のマクロ定義

//**************************
// インクルードファイル宣言
//**************************
#include "scene.h"

//**************************
// 前方宣言
//**************************
class CResultManager;

//*****************************
// リザルトシーンクラスを定義
//*****************************
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResult* Create(void);

private:
	CResultManager* m_pResultManager;	// マネージャークラスポインタ
};

#endif