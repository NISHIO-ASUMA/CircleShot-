//====================================================
//
// シーンファイル読み込み処理 [ sceneloader.h ]
// Author: Asuma Nishio
//
//====================================================

//**********************************
// スクリプトファイル読み込み処理
//**********************************
class CSceneLoader
{
public:
	// コンストラクタ・デストラクタ
	CSceneLoader();
	~CSceneLoader();

	// 静的メンバ関数
	static void SplitLoad(int nIdx);

private:

	// ファイルリスト
	static constexpr const char* m_aFileList[] = 
	{
		"data\\SceneText\\TitleObj.txt",// [0] タイトル
		"data\\SceneText\\TutoObj.txt",	// [1] チュートリアル
		"data\\SceneText\\GameObj.txt",	// [2] ゲーム
	};
};

