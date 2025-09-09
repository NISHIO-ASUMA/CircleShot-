//====================================
//
// タイトルui処理 [ titleui.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TITLEUI_H_ // このマクロ定義がされてなかったら
#define _TITLEUI_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2D.h"

//**********************
// 前方宣言
//**********************
class CObject;

//************************************
// タイトル2Dオブジェクトクラスを定義
//************************************
class CTitleUi : public CObject2D
{
public:
	//*********************
	// メニュー識別列挙型
	//*********************
	enum MENU
	{
		MENU_GAME,
		MENU_TUTORIAL,
		MENU_EXIT,
		MENU_MAX
	};

	// コンストラクタ・デストラクタ
	CTitleUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleUi();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(int nType);

	// 静的メンバ関数
	static CTitleUi* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fWidth,float fHeight,int nType);

private:
	int m_nTexIdx; // テクスチャインデックス
};

#endif