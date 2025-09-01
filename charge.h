//========================================
//
// チャージ処理 [ charge.h ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// インクルードファイル
//**********************************
#include "gage.h"

//****************************
// 前方宣言
//****************************
class CObject;

//****************************
// チャージクラスを定義
//****************************
class CCharge : public CGage
{
public:
	//***********************
	// テクスチャ種類列挙型
	//***********************
	enum CHARGE
	{
		CHARGE_FRAME,	// フレーム
		CHARGE_BAR,		// ゲージ本体
		CHARGE_MAX
	};

	// コンストラクタ・デストラクタ
	CCharge(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CCharge();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetType(int nType) { m_nType = nType; }
	void SetTexture(int nType);

	// 静的メンバ関数
	static CCharge* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
	static void AddCharge(float fValue);
	static void DecCharge(float fValue);

private:
	int m_nIdxTex;
	int m_nType;

	static float m_fCharge;
};

