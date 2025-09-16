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
#include "gage.h"

//**********************
// 前方宣言
//**********************
class CPlayer;
class CObject;

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

	// コンストラクタ・デストラクタ
	CPlayerLifeGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CPlayerLifeGage();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター・ゲッター
	void SetTexture(int Type);
	void SetGage(int type) { m_gage = type; }
	void SetShake(bool isFlags) { m_isShake = isFlags; }
	int GetGage(void) const { return m_gage; }
	
	// 静的メンバ関数
	static CPlayerLifeGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype);

private:
	static constexpr float GAGE_WIDTH = 40.0f;	// 基準値に掛ける倍率
	static constexpr float GAGE_HEIGHT = 45.0f; // ゲージの高さの固定値

	int m_nIdxTexture;		// テクスチャインデックス
	int m_nLifeLength;		// バーの長さ基準値
	int m_nMaxLifeLength;	// 最初の体力値
	int m_gage;				// 列挙変数
	int m_nMaxLife;			// 最大時の体力
	int m_nShakeTimer;		// 振動時間
	float m_fShakeAmplitude;// 振動量
	float m_fShakeOffset;	// オフセット

	bool m_isShake;			// 振動するかどうか

	CPlayer* m_pPlayer;		// プレイヤークラスポインタ
	D3DXVECTOR3 m_basePos;	// 基準座標
};

#endif
