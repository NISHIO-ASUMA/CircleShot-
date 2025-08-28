//====================================
//
// ポーズ処理 [ pause.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PAUSE_H_ // このマクロ定義がされてなかったら
#define _PAUSE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2D.h"

//**********************
// 前方宣言
//**********************
class CObject;

//**********************
// ポーズクラスを定義
//**********************
class CPause : public CObject2D
{
public:
	//******************
	// 選択肢列挙型
	//******************
	enum MENU
	{
		MENU_BACK,		// 背景
		MENU_RETRY,		// やり直し
		MENU_CONTINUE,  // 継続
		MENU_QUIT,		// タイトル遷移
		MENU_MAX
	};

	// コンストラクタ・デストラクタ
	CPause(int nPriority = static_cast<int>(CObject::PRIORITY::PAUSE));
	~CPause();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(void);
	void SetType(int nType) { m_nPauseType = nType; }

	// 静的メンバ関数
	static CPause* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, int nType);


private:
	int m_nIdxTexture;	// テクスチャインデックス番号
	int m_nPauseType;	// ポーズの種類
};

#endif
