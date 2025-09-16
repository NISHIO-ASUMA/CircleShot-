//=====================================
//
// ランキングシーン処理 [ ranking.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RANKING_H_ // このマクロ定義がされてなかったら
#define _RANKING_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル宣言
//******************************
#include "scene.h"

//******************************
// 前方宣言
//******************************

//******************************
// ランキングシーンクラスを定義
//******************************
class CRanking : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CRanking();
	~CRanking();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CRanking* Create(void);

private:

};

#endif