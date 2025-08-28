//============================================
//
// エディターシーン管理処理 [ editmanager.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _EDITMANAGER_H_ // このマクロ定義がされてなかったら
#define _EDITMANAGER_H_ // 2重インクルード防止のマクロ定義

//**********************************
// インクルードファイル
//**********************************
#include "modellist.h"

//**********************************
// 前方宣言
//**********************************
class CRubble;
class CMapManager;

//**********************************
// エディター管理クラスを定義
//**********************************
class CEditManager
{
public:
	//=====================
	// 書き出すパスの種類
	//=====================
	enum SAVEPASS
	{
		SAVEPASS_SMALL,
		SAVEPASS_MEDIUM,
		SAVEPASS_LARGE,
		SAVEPASS_MAX
	};

	// コンストラクタ・デストラクタ
	CEditManager();
	~CEditManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Save(void);
	void Reload(void);

	// セッター
	D3DXVECTOR3 SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	// ゲッター
	D3DXVECTOR3 GetPos() const { return m_pos; }
	D3DXVECTOR3 GetRot() const { return m_rot; }


private:
	//*******************************
	// ファイルパスを格納するリスト
	//*******************************
	const char* FILELIST[SAVEPASS_MAX] =
	{
		"data\\Loader\\RubbleList_small.txt",
		"data\\Loader\\RubbleList_medium.txt",
		"data\\Loader\\RubbleList_large.txt",
	};

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;

	CMapManager* m_pMapManager; // マネージャーポインタ

	int m_nTypeIdx; // インデックス
	int m_nSelectIndex; // 選択中オブジェクトのインデックス
	int m_nSavePassIdx;
	int m_nNumAll;		// 生成数
};

#endif
