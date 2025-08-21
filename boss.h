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
		TYPE_MAX
	};

	//***************************
	// 行動パターン列挙型
	//***************************
	enum ATTACKPATTERN
	{
		PATTERN_NONE, // 何も行動していない
		PATTERN_HAND, // 殴り
		PATTERN_IMPACT, // 叩きつけ
		PATTERN_CIRCLE, // 振り回し攻撃
		PATTERN_DEATH,	// 死亡モーション
		PATTERN_MAX
	};

	CBoss(int nPriority = static_cast<int>(CObject::PRIORITY::BOSS));
	~CBoss();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBoss* Create(D3DXVECTOR3 pos, float fSize,int nLife);

	D3DXVECTOR3 GetPos(void) { return m_pos;}
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	CParameter* GetParam(void) { return m_pParam; }

	float GetSize(void) { return m_fSize; }

	bool CollisionRightHand(D3DXVECTOR3* pPos);
	bool CollisionImpactScal(D3DXVECTOR3* pPos);

	static bool IsDaeth(void) { return m_isdaeth;}

	CModel*GetModelPartType(CModel::PARTTYPE modelpart);

	void Hit(int nDamage);

	void SetCoolTime(int nCooltime) { m_nCoolTime = nCooltime; }
	void DecCoolTime(void) { if (m_nCoolTime > 0) m_nCoolTime--; }
	int GetCoolTime(void) const { return m_nCoolTime; }

	CMotion* GetMotion(void) { return m_pMotion; }

	void ChangeState(CBossStateBace* pNewState, int Id); // ステート変更

	void RollToPlayer(void);

private:

	static constexpr int NUMMODELS = 21; // 使うモデル数

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;	// マトリックス

	CModel* m_pModel[NUMMODELS]; // モデルのポインタ
	CMotion* m_pMotion;		// モーションポインタ
	CParameter* m_pParam;	// パラメーターポインタ
	CStateMachine* m_pState; // ステートポインタ

	int m_type;			   // モーションの種類変数
	float m_fSize;		   // サイズ

	int m_nCoolTime;	// クールタイム
	int m_nCurrentMotion;
	bool m_isAttacked;  // 攻撃しているか
	static bool m_isdaeth;
};

#endif
