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
	// コンストラクタ・デストラクタ
	CResult();
	~CResult();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CResult* Create(void);

private:
	CResultManager* m_pResultManager;	// マネージャークラスポインタ
};

#endif