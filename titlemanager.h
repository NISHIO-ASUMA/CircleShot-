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
class CPointUi;
class CUi;

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
	//**************************
	// 定数格納構造体
	//**************************
	struct TITLEINFO
	{
		static constexpr int TITLE_MENU = 3;			// タイトル選択ui数
		static constexpr int SELECT_START = 0;			// 選択開始番号
		static constexpr int SELECT_END = 2;			// 選択最大値
		static constexpr int FLASHCOUNT = 10;			// 点滅間隔

		static constexpr float UIWIDTH = 195.0f;		// uiの横幅
		static constexpr float UIHEIGHT = 50.0f;		// uiの高さ
		static constexpr float SPREADWIDTH = 205.0f;	// 拡大横幅
		static constexpr float SPREADHEIGHT = 60.0f;	// 拡大高さ

		static constexpr float FIELDWIDTH = 1000.0f;	// 地面の広さ
		static constexpr float INTERVAL = 430.0f;		// 横幅の間隔
		static constexpr float SELECTPOS = 100.0f;		// 高さの間隔
	};

	TITLEINFO m_Info;			// 構造体変数

	int m_nIdx;					// 選択番号
	bool m_isuiCreate;			// 生成されたかどうかの判別フラグ
	bool m_isFirstuiCreate;		// 最初のシーンで生成されたか判別フラグ

	CTitleUi* m_pTitleui[TITLEINFO::TITLE_MENU]; // クラスポインタ配列
	CPointUi* m_pPointUi;			// クラスポインタ
	CUi* m_pUi;						// クラスポインタ
};

#endif

