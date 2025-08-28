//====================================
//
// タイトル処理 [ title.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TITLE_H_ // このマクロ定義がされてなかったら
#define _TITLE_H_ // 2重インクルード防止のマクロ定義

//****************************
// インクルードファイル宣言
//****************************
#include "scene.h"

//**************************
// 前方宣言
//**************************
class CTitleManager;

//****************************
// タイトルクラスを定義
//****************************
class CTitle :public CScene
{
public:
	// コンストラクタ・デストラクタ
	CTitle(bool isFirst = true);
	~CTitle();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTitle* Create(bool isFirst = true);

private:
	CTitleManager* m_pTitleManager; // マネージャークラスポインタ
	bool m_isCreate;				// ロゴ生成フラグ

};
#endif
