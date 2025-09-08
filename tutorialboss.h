//===========================================
//
// チュートリアルボス処理 [ tutoboss.h ]
// Author: Asuma Nishio
//
//===========================================

#ifndef _TUTORIALBOSS_H_ // このマクロ定義がされてなかったら
#define _TUTORIALBOSS_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// チュートリアルボスクラスを定義
//********************************
class CTutorialBoss : public CObject
{
public:
	//***************************
	// モーション列挙型宣言
	//***************************
	enum TYPE
	{
		TYPE_NEUTRAL = 0,	// ニュートラル
		TYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CTutorialBoss(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTutorialBoss();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CTutorialBoss* Create(D3DXVECTOR3 pos);

private:
	static constexpr int TUTO_MODEL = 21; // 使うモデル数

	D3DXVECTOR3 m_pos;		// 座表
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxworld;	// マトリックス

	CModel* m_pModel[TUTO_MODEL];	// モデルのポインタ
	CMotion* m_pMotion;				// モーションポインタ

};

#endif
