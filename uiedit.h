//====================================
//
// エディター処理 [ uiedit.h ]
// 
// TODO : 動的じゃなく普通に配列でやりたい
// Author: Asuma Nishio
//
//=====================================

#ifndef _UIEDIT_H_ // このマクロ定義がされてなかったら
#define _UIEDIT_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル宣言
//******************************
#include <vector>

//******************************
// 前方宣言
//******************************
class CUi;

//*******************************
// UIエディタークラスを定義
//*******************************
class CUiedit
{
public:
	CUiedit();
	~CUiedit();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void AddUi(D3DXVECTOR3 pos, int type, float width, float height);
	void SaveFile(const char* filename);
	void ReloadFile(const char* filename);

	//**********************
	// 構造体定義
	//**********************
	struct EditInfo
	{
		D3DXVECTOR3 pos;// 座標
		float fWidth;   // 横幅
		float fHeight;	// 高さ
		int nType;		// 種類
		CUi* pUi; // UIポインタ
	};

	// ゲッター
	std::vector<EditInfo>& GetEditInfoList() { return m_pUi; }

private:
	std::vector<EditInfo> m_pUi; // ui動的配列
};

#endif