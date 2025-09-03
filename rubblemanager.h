//=================================================
//
// 瓦礫オブジェクト管理処理 [ rubblemanager.h ]
// Author : Asuma Nishio
//
//=================================================

#ifndef _RUBBLEMANAGER_H_ // このマクロ定義がされてなかったら
#define _RUBBLEMANAGER_H_ // 2重インクルード防止のマクロ定義

//**********************************
// インクルードファイル
//**********************************
#include "rubble.h"
#include <vector>
#include <string>

//**********************************
// 瓦礫管理クラスを定義
//**********************************
class CRubbleManager
{
public:
	//*************************
	// 使うファイルパスの種類
	//*************************
	enum FILETYPE
	{
		FILETYPE_SMALL,		// 少なめ
		FILETYPE_MEDIUM,	// 普通
		FLIETYPE_lARGE,		// 多い
		FILETYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CRubbleManager();
	~CRubbleManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void LoadAllList(const char * pFileList);
	void LoadSplitFile(int type);

	// 静的メンバ関数
	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);
	static const std::vector<CRubble*>& GetRubbles() { return m_rubbles; } // 配列取得

private:
	static std::vector<CRubble*> m_rubbles; // 動的配列
	static int m_nIdxCount;					// モデルインデックス番号
	static constexpr const char* FILEPASS = "data\\Loader\\AllRubbleList.txt"; // ファイルパス

	std::vector<std::string> m_SubListFiles;	// AllRubbleListから読み込んだファイル群
	int m_nUseType;								// 使う種類
};

#endif
