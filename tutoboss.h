//==========================================
//
// チュートリアルボス処理 [ tutoboss.h ]
// Author: Asuma Nishio
//
//==========================================

#ifndef _TUTOBOSS_H_ // このマクロ定義がされてなかったら
#define _TUTOBOSS_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// チュートリアルボスクラスを定義
//********************************
class CTutoBoss : public CObject
{
	//***************************
	// モーション列挙型宣言
	//***************************
	enum TYPE
	{
		TYPE_NEUTRAL,	// ニュートラル
		TYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CTutoBoss(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTutoBoss();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTutoBoss* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:

	static constexpr int TUTOMODEL = 21; // 使うモデル数

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;	// マトリックス

	CModel* m_pModel[TUTOMODEL]; // モデルのポインタ
	CMotion* m_pMotion;		// モーションポインタ
	int m_nType;

};

#endif