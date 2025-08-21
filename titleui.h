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
	//********************
	// メニュー識別列挙型
	//********************
	enum MENU
	{
		MENU_GAME,
		MENU_TUTORIAL,
		MENU_MAX
	};

	CTitleUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitleUi* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fWidth,float fHeight,int nType);

	void SetTexture(int nType);

private:
	int m_nTexIdx; // テクスチャインデックス
};

#endif