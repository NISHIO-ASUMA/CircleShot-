//====================================
//
// プレイヤー処理 [ player.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PLAYER_H_ // このマクロ定義がされてなかったら
#define _PLAYER_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// 前方宣言
//**********************
class CShadow;
class CInputKeyboard;
class CJoyPad;
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CPlayerStateBase;

//*************************
// プレイヤークラスを定義
//*************************
class CPlayer : public CObject
{
public:
	//***********************************
	// プレイヤーが行うモーション列挙型
	//***********************************
	enum PLAYERMOTION
	{
		PLAYERMOTION_NEUTRAL,		// ニュートラル
		PLAYERMOTION_MOVE,			// 移動
		PLAYERMOTION_ACTION,		// アクション
		PLAYERMOTION_JUMP,			// ジャンプ
		PLAYERMOTION_LANDING,		// 着地
		PLAYERMOTION_JUMPATTACK,	// SP攻撃
		PLAYERMOTION_DAMAGE,		// 吹き飛ばし
		PLAYERMOTION_WAKEUP,		// 起き上がり
		PLAYERMOTION_MAX
	};

	CPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::PLAYER));
	~CPlayer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, const int nIdxParson,const char * pFilename); // 生成処理

	D3DXVECTOR3 GetPos(void) { return m_pos; } // 現在の座標を取得
	D3DXVECTOR3 GetRot(void) { return m_rot; } // 現在の角度を取得
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; } // 目的角を取得

	void SetRotDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
	bool IsJumping() { return m_isJump; } 	// ジャンプ状態の確認
	void SetJump(bool isJump) { m_isJump = isJump; }
	void SetLanding(bool isLanding) { m_isLanding = isLanding; }

	static CPlayer* GetIdxPlayer(int Idx); // インデックス番号で取得
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	CModel* GetModelPartType(CModel::PARTTYPE modelpart);
	int GetType(void) { return m_type; }

	void ChangeState(CPlayerStateBase* pNewState,int Id); // ステート変更
	CStateMachine* GetStateMachine(){return m_pStateMachine;}	// プレイヤーのステートマシンを取得

	CMotion* GetMotion(void) { return m_pMotion; }
	CParameter* GetParameter(void) { return m_pParameter;}

	void UpdateAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestPos, CJoyPad* pPad); // 通常攻撃更新関数
	void UpdateMove(const D3DXVECTOR3 DestPos, CInputKeyboard* pInputKeyboard,CJoyPad * pPad);   // 移動更新関数
	void UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad);

	void Collision(void);
	void AddMove(void) {m_pos += m_move;}

	void SetValue(float fValue) {m_fValue = fValue;}
	void JumpMove(void) { m_move.y = m_fValue; }

	D3DXVECTOR3 VecToBoss(const D3DXVECTOR3& pPos);

	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);
	bool isAttackeyPress(CInputKeyboard* pKeyInput);

	bool isLanding(void) { return m_isJump; }
	void InitPos(float fAngle);

	void StartJump(void);
	void GravityScal(void);

	static bool IsDeath(void) { return m_isDeath; }

	static inline constexpr int MAX_MODEL = 19; // プレイヤーで使うモデルの数
	PLAYERMOTION GetNowMotion(void) const;

	void HitDamage(int nDamage);	// 判定処理

private:

	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_rotDest;  // 目的角

	D3DXVECTOR3 m_pos;		// 階層構造設定座標
	D3DXVECTOR3 m_posOld;	// 過去の座標情報
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス

	CModel* m_apModel[MAX_MODEL]; // 使うモデルのポインタ
	CMotion* m_pMotion;		// モーションのポインタ
	CShadow* m_pShadow;		// 影クラスのポインタ変数
	CParameter* m_pParameter; // パラメータークラスポインタ
	CShadowS* m_pShadowS;	// ステンシルシャドウクラスポインタ
	CStateMachine* m_pStateMachine;	// ステート基底クラスのポインタ

	int m_type;				// モーションの種類変数
	int m_nNumAll;		    // モデル総数
	int m_State;			// 状態管理カウンター
	int m_nIdxTexture;		// テクスチャID

	bool m_isLanding;		// 着地判定
	bool m_isJump;			// ジャンプ判定
	bool m_isMoving;		// 移動キー判定
	bool m_isAttack;		// 攻撃判定
	bool m_isShadow;
	bool m_isStateSynchro;
	static bool m_isDeath;

	bool m_isConectPad;

	float m_fAngle;			// 現在の角度
	int m_nIdxPlayer;		// プレイヤーの識別番号

	const char* m_pFilename; // 読み込むファイル名

	float m_fValue;

};

#endif