//====================================
//
// ライト処理 [ light.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _LIGHT_H_ // このマクロ定義がされてなかったら
#define _LIGHT_H_ // 2重インクルード防止のマクロ定義

//**********************
// ライトクラスを定義
//**********************
class CLight
{
public:
	// コンストラクタ・デストラクタ
	CLight();
	~CLight();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	static inline constexpr int NUMLIGHT = 3;		// 設置する数

	D3DLIGHT9 m_aLight[NUMLIGHT]; // ライト数
	D3DXVECTOR3 m_vecDir[NUMLIGHT];	// ベクトル
};

#endif