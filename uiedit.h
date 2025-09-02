//=====================================
//
// UIエディターシーン処理 [ uiedit.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _UIEDIT_H_ // このマクロ定義がされてなかったら
#define _UIEDIT_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル宣言
//******************************
#include "scene.h"

//*******************************
// 前方宣言
//*******************************
class CUimanager;
class CUiEditManager;

//*******************************
// UIエディタークラスを定義
//*******************************
class CUiedit : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CUiedit();
	~CUiedit();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CUiedit* Create(void);

private:
	CUiEditManager* m_pUiEditManager;	// クラスポインタ
};

#endif