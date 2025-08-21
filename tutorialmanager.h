//=============================================
//
// チュートリアル管理処理 [ tutorialmanager.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTORIALMANAGER_H_ // このマクロ定義がされてなかったら
#define _TUTORIALMANAGER_H_ // 2重インクルード防止のマクロ定義

//******************************
// 前方宣言
//******************************
class CTutorialUi;

//******************************
// マネージャー管理クラスを定義
//******************************
class CTutorialManager
{
public:
	CTutorialManager();
	~CTutorialManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CTutorialUi* m_pTutoui; // チュートリアルuiクラスのポインタ

};

#endif
