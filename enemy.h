//====================================
//
// 敵の処理 [ enemy.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _ENEMY_H_ // このマクロ定義がされてなかったら
#define _ENEMY_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include "objectX.h"

//**************************
// 前方宣言
//**************************
class CParameter;
class CStateMachine;
class CEnemyStateBase;

//**************************
// 敵クラスを定義
//**************************
class CEnemy : public CObjectX
{
public:
	//*********************
	// 敵の行動管理列挙型  これをステートマシーンにする
	//*********************
	enum STATE
	{
		STATE_FALL,
		STATE_ROLLING,
		STATE_DEATH,
		STATE_MAX
	};

	//*********************
	// 敵の種類列挙型
	//*********************
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_RIGHT,
		TYPE_KEFT,
		TYPE_MAX
	};

	// これは消す　ステートマシン作って
	typedef enum
	{
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_NORMAL,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	CEnemy(int nPriority = static_cast<int>(CObject::PRIORITY::ENEMY));
	~CEnemy();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	static CEnemy* Create(const char* pFileName, const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE nType, int nHp);
	static int GetEnemy(void) { return m_NumEnemy; }

	void SetType(const TYPE type) { m_Type = type; }
	TYPE GetType(void) const { return m_Type; }

	void HitEnemy(int nDamage);
	bool Collision(D3DXVECTOR3* pPos);
	void ChangeState(CEnemyStateBase* pNewState, int id);

	void UpdateMoving(void);

private:
	D3DXVECTOR3 m_move;		// 移動量
	TYPE m_Type;			// 種類
	ENEMYSTATE m_State;		// 敵の状態
	CParameter* m_pParam;	// パラメータークラスポインタ
	CStateMachine* m_pStateMachine;	// ステート基底クラスのポインタ

	static int m_NumEnemy;	// 敵数管理
	int m_StateCount;		// 状態管理用
	int m_nMoveCount;		// 移動継続時間のカウント

	// クォータニオン用
	D3DXMATRIX m_mtxRot;	// 回転マトリックス
	D3DXQUATERNION m_quat;	// クォータニオン
	D3DXVECTOR3 m_VecAxis;	// 回転軸
	float m_fValueRot;		// 回転角度

	float m_fAngle; // 現在の回転角
	float m_fRadius; // 回転半径

};
#endif
