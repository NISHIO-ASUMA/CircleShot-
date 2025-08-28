//=============================================
//
// チュートリアルUI処理 [ tutorialui.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTORIALUI_H_ // このマクロ定義がされてなかったら
#define _TUTORIALUI_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル宣言
//******************************
#include "object2D.h"

//******************************
// チュートリアルuiクラスを定義
//******************************
class CTutorialUi : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CTutorialUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTutorialUi();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(int nType);

	// 静的メンバ関数
	static CTutorialUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);

private:
	int m_nIdxTexture;	// テクスチャインデックス
};

#endif
