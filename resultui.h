//=====================================
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
	// UIの種類列挙型
	//********************
	enum TYPE
	{
		TYPE_NONE,
		MENU_MAX
	};

	// コンストラクタ・デストラクタ
	CResultUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultUi();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(int nType);

	// 静的メンバ関数
	static CResultUi* Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType);

private:
	int m_nIdxTex;		// テクスチャインデックス

};

#endif
