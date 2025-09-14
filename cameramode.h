//=========================================
//
// カメラ作成シーン処理 [ cameramode.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _CAMERAMODE_H_ // このマクロ定義がされてなかったら
#define _CAMERAMODE_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル
//******************************
#include "scene.h"

//******************************
// シーンクラスを定義
//******************************
class CCameraMode : public CScene
{
public:
	// コンストラクタ・デストラクタ
	CCameraMode();
	~CCameraMode();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 生成処理
	static CCameraMode* Create(void);
};

#endif