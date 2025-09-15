//==============================================================
//
// カメラアニメーション時に適用するUI処理 [ moveui.h ]
// Author: Asuma Nishio
//
//==============================================================

#ifndef _MOVEUI_H_ // このマクロ定義がされてなかったら
#define _MOVEUI_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2D.h"

//********************************************************
// カメラアニメーション時に適用するUIクラス
//********************************************************
class CMoveUi : public CObject2D
{
public:
	//**********************
	// 移動方向種類
	//**********************
	enum MOVETYPE
	{
		MOVETYPE_RIGHT,
		MOVETYPE_LEFT,
		MOVETYPE_CENTER,
		MOVETYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CMoveUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CMoveUi();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetTexture(const char* pRegistername);

	// 静的メンバ関数
	static CMoveUi* Create(D3DXVECTOR3 pos, const char* pFileName, MOVETYPE type);

private:
	int m_nIdxTexture;	// テクスチャインデックス
	MOVETYPE m_nMoveType;	// 移動種類
};
#endif