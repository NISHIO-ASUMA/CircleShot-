//====================================
//
// 背景処理 [ bg.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BG_H_ // このマクロ定義がされてなかったら
#define _BG_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************

#include "object2D.h"

//**********************
// 背景クラスを宣言
//**********************
class CBg : public CObject2D
{
public:
	// 背景種類
	typedef enum
	{
		BG_BACK = 0,
		BG_CENTER,
		BG_FRONT,
		BG_MAX
	}BG;

	CBg(int nPriority = 2);
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBg* Create(int nIdxBg);

	void SetTexture(int nType);

private:
	void SetScrollSpeed(float speed) { m_ScrollSpeed = speed; }	// スクロール関数

	D3DXVECTOR2 m_TexScroll;	// テクスチャスクロール変数

	int m_IndexBg;				// レイヤー番号
	float m_ScrollSpeed;		// スクロールの速度

	static LPDIRECT3DTEXTURE9 m_pTexture[BG_MAX]; // テクスチャポインタ


	int m_nIdxTexture;

};

#endif