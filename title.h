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
	CTitle(bool isFirst = true);
	~CTitle();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitle* Create(bool isFirst = true);

private:
	CTitleManager* m_pTitleManager; // クラスポインタ
	bool m_isCreate;			// 生成フラグ

};
#endif
