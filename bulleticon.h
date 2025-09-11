//========================================
//
// 弾アイコン処理 [ bulleticon.h ]
// Author: Asuma Nishio
//
//========================================

#ifndef _BULLETICON_H_ // このマクロ定義がされてなかったら
#define _BULLETICON_H_ // 2重インクルード防止のマクロ定義

//***************************
// インクルードファイル宣言
//***************************
#include "object2D.h"

//***************************
// 弾アイコン表示クラス定義
//***************************
class CBulletIcon : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CBulletIcon(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBulletIcon();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(const char * pTexName);

	// 静的メンバ関数
	static CBulletIcon* Create(D3DXVECTOR3 pos, const char* pTexName, int nIdx);

private:
	int m_nIdxTex;	// テクスチャインデックス
	int m_nIdx;
};

#endif