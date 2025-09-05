//====================================================
//
// チュートリアルプレイヤー処理 [ tutoplayer.h ]
// Author: Asuma Nishio
//
//====================================================

#ifndef _TUTOPLAYER_H_ // このマクロ定義がされてなかったら
#define _TUTOPLAYER_H_ // 2重インクルード防止のマクロ定義

#if 0
//********************************
// インクルードファイル宣言
//********************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// 前方宣言
//********************************
class CShadowS;
class CStateMachine;
class CPlayerStateBase;

//****************************************
// チュートリアルプレイヤークラスを定義
//****************************************
class CTutoPlayer : public CObject
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
		PLAYERMOTION_JUMPATTACK,	// ジャンプ攻撃
		PLAYERMOTION_DAMAGE,		// ダメージ
		PLAYERMOTION_MAX
	};

	// コンストラクタ・デストラクタ
	CTutoPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTutoPlayer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	// 静的メンバ関数
	static CTutoPlayer* Create(D3DXVECTOR3 pos, const int nIdx, const char* pFileName);
	static CTutoPlayer* GetIdxPlayer(int Idx);

private:
	static inline constexpr int TUTOMODEL = 19; // 階層構造モデル数

	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_rotDest;  // 目的角

	D3DXVECTOR3 m_pos;		// 階層構造設定座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス

	CModel* m_apModel[TUTOMODEL]; // 使うモデルのポインタ
	CMotion* m_pMotion;		// モーションのポインタ

	int m_nIdxPlayer;		// プレイヤーの識別番号
	const char* m_pFilename; // 読み込むファイル名

	CShadowS* m_pShadowS;	// ステンシルシャドウクラスポインタ
	CStateMachine* m_pStateMachine;	// ステート基底クラスのポインタ

	int m_type;				// モーションの種類変数
	int m_nNumAll;			// モデル総数
	int m_State;			// 状態管理カウンター
	int m_nIdxTexture;		// テクスチャID
	int m_nIdxPlayer;		// プレイヤーの識別番号

	bool m_isLanding;		// 着地判定
	bool m_isJump;			// ジャンプ判定
	bool m_isMoving;		// 移動キー判定
	bool m_isAttack;		// 攻撃判定
	bool m_isShadow;
	bool m_isStateSynchro;

	float m_fAngle;			// 現在の角度
	float m_fValue;

	const char* m_pFilename; // 読み込むファイル名
};
#endif

#endif