//====================================
//
// リザルトui処理処理 [ resultui.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RESULTUI_H_ // このマクロ定義がされてなかったら
#define _RESULTUI_H_ // 2重インクルード防止のマクロ定義

//****************************
// インクルードファイル宣言
//****************************
#include "object2D.h"

//**********************
// 前方宣言
//**********************
class CObject;

//****************************
// リザルトUIクラスを定義
//****************************
class CResultUi : public CObject2D
{
public:

	//********************
	// 列挙型
	//********************
	enum TYPE
	{
		TYPE_NONE,
		MENU_MAX
	};

	CResultUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultUi();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CResultUi* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType);

	void SetTexture(int nType);

private:
	int m_nIdxTex;		// テクスチャインデックス

};

#endif
