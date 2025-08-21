//=========================================
//
// タイトルプレイヤー処理 [ titleplayer.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _TITLEPLAYER_H_ // このマクロ定義がされてなかったら
#define _TITLEPLAYER_H_ // 2重インクルード防止のマクロ定義

//********************************
// インクルードファイル宣言
//********************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// 前方宣言
//********************************
class CInputKeyboard;
class CShadowS;

//********************************************
// タイトルプレイヤーオブジェクトクラスを定義
//********************************************
class CTitlePlayer : public CObject
{
public:
	//***********************
	// 使用モーション
	//***********************
	enum TITLEMOTION
	{
		TITLEMOTION_NEUTORAL,
		TITLEMOTION_ACTION,
		TITLEMOTION_MAX
	};

	CTitlePlayer(int nPriority = static_cast<int>(CObject::PRIORITY::PLAYER));
	~CTitlePlayer();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTitlePlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const int nIdxParson, const char* pFilename); // 生成処理

	static CTitlePlayer* GetIdxPlayer(int Idx); // インデックス番号で取得
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	D3DXVECTOR3 GetPos(void) { return m_pos; }

private:

	static inline constexpr int TITLE_MODEL = 19; // 階層構造モデル数

	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_rotDest;  // 目的角

	D3DXVECTOR3 m_pos;		// 階層構造設定座標
	D3DXVECTOR3 m_rot;		// 角度
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス

	CModel* m_apModel[TITLE_MODEL]; // 使うモデルのポインタ
	CMotion* m_pMotion;		// モーションのポインタ

	int m_nIdxPlayer;		// プレイヤーの識別番号
	const char* m_pFilename; // 読み込むファイル名

};

#endif