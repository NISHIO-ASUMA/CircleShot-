//=========================================
//
// ボス体力処理 [ bosslifegage.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _BOSSLIFEGAGE_H_ // このマクロ定義がされてなかったら
#define _BOSSLIFEGAGE_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include "gage.h"

//**********************
// 前方宣言
//**********************
class CBoss;

//***************************
// ボス体力管理クラスを定義
//***************************
class CBossLifeGage : public CGage
{
public:
	//***********************
	// ゲージの種類
	//***********************
	enum TYPE
	{
		TYPE_FRAME,
		TYPE_GAGE,
		TYPE_MAX
	};

	CBossLifeGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBossLifeGage();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetType(int nType) { m_Type = nType; }
	void SetTexture(int nType);

	static CBossLifeGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);

private:
	int m_nCurrentLifeLength;		// バーの長さ基準値
	int m_nMaxLifeLength;	// 最大体力時の長さ
	int m_Type;				// 列挙変数

	int m_nIdxTex;	// テクスチャインデックス
	CBoss* m_pBoss; // ボスのポインタ

};

#endif

