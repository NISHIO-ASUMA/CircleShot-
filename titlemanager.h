//==========================================
//
// タイトル管理処理 [ titlemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

#ifndef _TITLEMANAGER_H_ // このマクロ定義がされてなかったら
#define _TITLEMANAGER_H_ // 2重インクルード防止のマクロ定義

//**************
// 前方宣言
//**************
class CTitleUi;

//**************************************
// タイトルマネージャー管理クラスを定義
//**************************************
class CTitleManager
{
public:
	// コンストラクタ・デストラクタ
	CTitleManager(bool isCreate = true);
	~CTitleManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	static constexpr int TITLE_MENU = 2;			// タイトルui数
	static constexpr int SELECT_START = 0;			// 選択開始番号
	static constexpr int SELECT_END = 1;			// 最大値

	static constexpr float DIGITPOS = 160.0f;		 // uiの幅
	static constexpr float UIWIDTH = 270.0f;		// uiの横幅
	static constexpr float UIHEIGHT = 50.0f;		// uiの高さ
	static constexpr float FIELDWIDTH = 1000.0f;	// 地面の広さ

	int m_nIdx;		// 選択番号
	bool m_isuiCreate;			// 生成されたかどうかの判別フラグ
	bool m_isFirstuiCreate;		// 最初のシーンで生成されたか判別フラグ

	CTitleUi* m_pTitleui[TITLE_MENU]; // クラスポインタ
};

#endif

