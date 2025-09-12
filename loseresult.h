//============================================
//
// 負けリザルトシーン処理 [ loseresult.h ]
// Author: Asuma Nishio
// 
//============================================

#ifndef _LOSERESULT_H_ // このマクロ定義がされてなかったら
#define _LOSERESULT_H_ // 2重インクルード防止のマクロ定義

//**************************
// インクルードファイル宣言
//**************************
#include "scene.h"

//********************************
// 負けリザルトシーンクラスを定義
//********************************
class CLoseResult : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CLoseResult();
	~CLoseResult();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CLoseResult* Create(void);

private:

};

#endif