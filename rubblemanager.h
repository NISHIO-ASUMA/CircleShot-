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
		FILETYPE_SMALL,
		FILETYPE_MEDIUM,
		FLIETYPE_lARGE,
		FILETYPE_MAX
	};

	CRubbleManager();
	~CRubbleManager();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Load(void);

	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:
	static std::vector<CRubble*> m_rubbles; // 動的配列
	static int m_nIdxCount;	// モデルインデックス番号

	static constexpr const char* FILEPASS = "data\\Loader\\RubbleList.txt"; // ファイルパス

};

#endif
