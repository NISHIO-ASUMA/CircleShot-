//=============================================
//
// チュートリアルタスク処理 [ tutotask.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTOTASK_H_ // このマクロ定義がされてなかったら
#define _TUTOTASK_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル
//******************************
#include <string>
#include <vector>

//******************************
// 前方宣言
//******************************
class CTutorialUi;

//********************************
// タスククラスを定義
//********************************
class CTutoTask
{
public:
	//**************************
	// 読み込み情報構造体
	//**************************
	struct TASKINFO
	{
		D3DXVECTOR3 pos;	// 座標
		float fWidth;		// 横幅
		float fHeight;		// 高さ
		std::string TexName; // テクスチャ名
		int nState;			// 状態
	};

	// コンストラクタ・デストラクタ
	CTutoTask();
	~CTutoTask();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Load(void);
	void NextTask(void);

	// ゲッター
	int GetTaskIndex() const { return m_nCurrentIndex; }

private:
	std::vector<TASKINFO>m_pTutoUi;	// 動的配列
	int m_nCurrentIndex;			// 今のタスク番号
	CTutorialUi* m_pCurrentUi;		// 表示中のUI
	TASKINFO m_Info;				// 構造体変数

	void CreateTaskUi(int index);	// 生成
};


#endif

