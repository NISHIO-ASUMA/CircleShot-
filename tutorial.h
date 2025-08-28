//=====================================
//
// チュートリアル処理 [ tutorial.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TUTORIAL_H_ // このマクロ定義がされてなかったら
#define _TUTORIAL_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "scene.h"

//**********************
// 前方宣言
//**********************
class CTutorialManager;

//************************************
// チュートリアルシーンクラスを定義
//************************************
class CTutorial : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CTutorial();
	~CTutorial();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTutorial* Create(void);

private:
	CTutorialManager* m_pTutoManager; // マネージャークラスのポインタ
};

#endif
