//=========================================
//
// プレイヤー体力処理 [ playerlifegage.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _PLAYERLIFEGAGE_H_ // このマクロ定義がされてなかったら
#define _PLAYERLIFEGAGE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include "gage.h"

//**********************
// 前方宣言
//**********************
class CPlayer;

//*************************
// 体力ゲージクラスを定義
//*************************
class CPlayerLifeGage : public CGage
{
public:
	//**********************
	// ゲージの種類定義
	//**********************
	enum GAGE
	{
		GAGE_FRAME,
		GAGE_BAR,
		GAGE_MAX
	};

	CPlayerLifeGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CPlayerLifeGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayerLifeGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype);

	void SetTexture(int Type);
	int GetGage(void) const { return m_gage; }
	void SetGage(int type) { m_gage = type; }

private:
	static constexpr float GAGE_WIDTH = 40.0f;	// 基準値に掛ける倍率
	static constexpr float GAGE_HEIGHT = 45.0f; // ゲージの高さの固定値

	int m_nIdxTexture;		// テクスチャインデックス
	int m_nLifeLength;		// バーの長さ基準値
	int m_nMaxLifeLength;	// 最初の体力値
	CPlayer* m_pPlayer;		// プレイヤークラスポインタ
	int m_gage;			// 列挙変数


};

#endif
