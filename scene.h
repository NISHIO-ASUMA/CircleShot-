//====================================
//
// シーン処理 [ scene.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SCENE_H_ // このマクロ定義がされてなかったら
#define _SCENE_H_ // 2重インクルード防止のマクロ定義

//******************************
// シーンクラスを定義
//******************************
class CScene 
{
public:
	//*************************
	// シーンの種類列挙型
	//*************************
	enum MODE
	{
		MODE_NONE,		// 何も無い
		MODE_TITLE,		// タイトル
		MODE_TUTORIAL,	// チュートリアル
		MODE_GAME,		// ゲーム
		MODE_RESULT,	// リザルト
		MODE_RANKING,	// ランキング
		MODE_EDIT,		// 配置モード
		MODE_MAX
	};

	CScene(MODE mode);
	virtual ~CScene();

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	MODE GetScene(void) const { return m_Scene; }

private:
	MODE m_Scene;	// シーン管理変数
};

#endif
