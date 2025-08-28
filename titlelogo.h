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
	static CTitleLogo* Create(D3DXVECTOR3 pos,float fWidth, float fHeight, int nAnchorType);

private:
	int m_nTexIdx;		// テクスチャインデックス
};

#endif
