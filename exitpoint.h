//====================================
//
// 出口ポイント処理 [ exitpoint.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _EXITPOINT_H_ // このマクロ定義がされてなかったら
#define _EXITPOINT_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object3D.h"

//**********************
// ポイントクラスを定義
//**********************
class CExitPoint : public CObject3D
{
public:
	// コンストラクタ・デストラクタ
	CExitPoint(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CExitPoint();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);
	bool Collision(D3DXVECTOR3 * DestPos);

	// 静的メンバ関数
	static CExitPoint* Create(D3DXVECTOR3 pos, float fWidth);

private:
	int m_nIdxTex;	// テクスチャインデックス
};

#endif