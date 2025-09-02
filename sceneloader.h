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
	CSceneLoader();
	~CSceneLoader();

	static void SplitLoad(int nIdx);

private:
	static constexpr int NUMFILE = 2;

	// ファイルリスト
	static constexpr const char* m_aFileList[] = {
		"data\\SceneText\\TutoObj.txt",	// [0] チュートリアル
		"data\\SceneText\\GameObj.txt",	// [1] ゲーム
	};

};

