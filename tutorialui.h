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
	CTutorialUi();
	~CTutorialUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorialUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);

	void SetTexture(int nType);

private:
	int m_nIdxTexture;	// テクスチャインデックス
};

#endif
