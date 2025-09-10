//=========================================
//
// タイトルロゴ処理 [ titlelogo.h ]
// Author: Asuma Nishio
// 
//==========================================

#ifndef _TITLELOGO_H_ // このマクロ定義がされてなかったら
#define _TITLELOGO_H_ // 2重インクルード防止のマクロ定義

//***************************
// インクルードファイル宣言
//***************************
#include "object2D.h"

//***************************
// 前方宣言
//***************************
class CObject;

//***************************
// タイトルロゴクラス定義
//***************************
class CTitleLogo : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CTitleLogo(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleLogo();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(void);

	// 静的メンバ関数
	static CTitleLogo* Create(D3DXVECTOR3 pos,float fWidth, float fHeight);

private:
	int m_nTexIdx;		// テクスチャインデックス
	D3DXVECTOR3 m_move;	// 移動量
	bool m_isAnimating;  // アニメーション中か
	int  m_nFrame;		// 経過フレーム数
	int  m_nMaxFrame;	// アニメーション時間
};

#endif
