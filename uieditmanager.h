//=================================================
//
// UIエディターシーン管理処理 [ uieditmanager.h ]
// Author : Asuma Nishio
// 
// TODO : 家で作業する
//
//=================================================

#ifndef _UIEDITMANAGER_H_ // このマクロ定義がされてなかったら
#define _UIEDITMANAGER_H_ // 2重インクルード防止のマクロ定義

//**********************************
// 管理クラスを定義
//**********************************
class CUiEditManager
{
public:
	//=====================
	// 書き出すパスの種類
	//=====================
	enum SAVEPASS
	{
		SAVEPASS_TUTO,
		SAVEPASS_GAME,
		SAVEPASS_MAX
	};

	// コンストラクタ・デストラクタ
	CUiEditManager();
	~CUiEditManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);

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
		"data\\Loader\\ui_tuto.txt",
		"data\\Loader\\ui_game.txt",
	};

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;

	int m_nTypeIdx; // インデックス
	int m_nSelectIndex; // 選択中オブジェクトのインデックス
	int m_nSavePassIdx;
	int m_nNumAll;		// 生成数

};
#endif

