//=======================================
//
// モデルファイルリスト [ modellist.h ]
// Author: Asuma Nishio
//
//=======================================

#ifndef _MODELLIST_H_ // このマクロ定義がされてなかったら
#define _MODELLIST_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include <vector>

//**********************
// 読み込みクラスを定義
//**********************
class CModelList
{
public:
	//*************************
	// 情報保存用構造体
	//************************* 
	struct MODELINFO
	{
		LPD3DXMESH pMesh;		// メッシュのポインタ
		LPD3DXBUFFER pBuffMat;	// マテリアルのポインタ
		DWORD dwNumMat;			// マテリアル数
		std::vector<int>pTexture; // テクスチャの動的ポインタ
		char FileName[MAX_WORD];		// 文字列
	};

	// コンストラクタ・デストラクタ
	CModelList();
	~CModelList();

	// 静的メンバ関数
	static void Load(void);
	static void UnLoad(void);
	static MODELINFO GetInfo(const int Indx) { return m_ModelInfo[Indx]; };
	static std::vector <MODELINFO> GetInfo() { return m_ModelInfo; }

private:
	static std::vector<MODELINFO>m_ModelInfo; // 動的配列
	static constexpr const char* MODELLIST = "data\\Loader\\ModelFile.txt"; // ファイルパス

};

#endif