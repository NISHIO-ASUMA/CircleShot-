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
class CTutoTask;

//********************************
// チュートリアル管理クラスを定義
//********************************
class CTutorialManager
{
public:
	//***********************
	// 動かすタスクの種類
	//***********************
	enum TASKTYPE
	{
		TASKTYPE_MOVE,
		TASKTYPE_ATTACK,
		TASKTYPE_JUMP,
		TASKTYPE_JUMPATTACK,
		TASKTYPE_LASER,
		TASKTYPE_LASERACTION,
		TASKTYPE_FREE,
		TASKTYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CTutorialManager();
	~CTutorialManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CTutorialUi* m_pTutoui; // チュートリアルuiクラスのポインタ
	CTutoTask* m_pTask;		// タスククラスポインタ	
	TASKTYPE m_Tasktype;	// 種類
	bool m_isFreeDone;
};

#endif
