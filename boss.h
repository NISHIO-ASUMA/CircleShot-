//====================================
//
// ボス処理 [ boss.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BOSS_H_ // このマクロ定義がされてなかったら
#define _BOSS_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// 前方宣言
//**********************
class CParameter;
class CStateMachine;
class CBossStateBace;

//**********************
// ボスクラスを定義
//**********************
class CBoss : public CObject
{
public:
	//***************************
	// モーション列挙型宣言
	//***************************
	enum TYPE
	{
		TYPE_NEUTRAL = 0,	// ニュートラル
		TYPE_ACTION,		// 腕攻撃
		TYPE_IMPACT,		// 叩きつけ衝撃波
		TYPE_RUBBLE,		// 瓦礫攻撃
		TYPE_CIRCLE,		// 薙ぎ払い
		TYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CBoss(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CBoss();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CollisionRightHand(D3DXVECTOR3* pPos);
	bool CollisionImpactScal(D3DXVECTOR3* pPos);
	bool CollisionCircle(D3DXVECTOR3* pPos);
	void Hit(int nDamage,D3DXVECTOR3 HitPos);
	void ChangeState(CBossStateBace* pNewState, int Id);
	void RollToPlayer(void);
	void DecCoolTime(void) { if (m_nCoolTime > 0) m_nCoolTime--; }

	// セッター
	void SetCoolTime(int nCooltime) { m_nCoolTime = nCooltime; }
	void SetWeekPoint(const D3DXVECTOR3 pos) { m_WeekPointPos = pos; }

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos;}
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	CParameter* GetParam(void) { return m_pParam; }

	float GetSize(void) { return m_fSize; }
	int GetCoolTime(void) const { return m_nCoolTime; }
	CMotion* GetMotion(void) { return m_pMotion; }

	// 静的メンバ関数
	static CBoss* Create(D3DXVECTOR3 pos, float fSize,int nLife);
	static bool IsDaeth(void) { return m_isdaeth;}
	CModel*GetModelPartType(CModel::PARTTYPE modelpart);

private:

	static constexpr int NUMMODELS = 21; // 使うモデル数
	static constexpr float WEEKPOINTSIZE = 100.0f;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_WeekPointPos;
	D3DXMATRIX m_mtxworld;	// マトリックス

	CModel* m_pModel[NUMMODELS]; // モデルのポインタ
	CMotion* m_pMotion;		// モーションポインタ
	CParameter* m_pParam;	// パラメーターポインタ
	CStateMachine* m_pState; // ステートポインタ

	int m_type;				// モーションの種類変数
	int m_nCoolTime;		// クールタイム
	int m_nCurrentMotion;

	float m_fSize;			// サイズ
	bool m_isEvent;			// イベントを行ったか
	
	static bool m_isdaeth;
};

#endif
