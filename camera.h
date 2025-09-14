//=====================================
//
// カメラ処理 [ camera.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _CAMERA_H_ // このマクロ定義がされてなかったら
#define _CAMERA_H_ // 2重インクルード防止のマクロ定義

//**********************
// 前方宣言
//**********************
class CInputMouse;

//**********************
// カメラクラスを定義
//**********************
class CCamera
{
public:
	//**********************
	// カメラモード列挙型
	//**********************
	enum MODE
	{
		MODE_NONE,
		MODE_PLAYER,
		MODE_LOCKON,
		MODE_MOUSE,
		MODE_EVENT,
		MODE_SHAKE,
		MODE_ANIM,
		MODE_MAX
	};

	// コンストラクタ・デストラクタ
	CCamera();
	~CCamera();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	void MouseView(CInputMouse* pMouse);
	void LockOn(void);
	void PlayerFollow(void);
	void Rotation(void);
	void TitleCamera(void);
	void TutorialCamera(void);
	void AnimCamera(void);
	void UpdateAnimCamera(void);

	void Load(void);
	void Save(void);

	// セッター
	void StartEventCamera(const D3DXVECTOR3& targetV, const D3DXVECTOR3& targetR, int endFrame);
	void ShakeCamera(int WaveTime);
	void SetIsRotation(bool isFlags) { m_isRotation = isFlags; }
	void SetFinishRotation(bool isFlags) { m_isStopRotation = isFlags; }
	void SetCameraMode(int nMode) { m_pCamera.nMode = nMode; }
	void SetKey(bool isFlags) { m_isKey = isFlags; }

	// ゲッター
	D3DXVECTOR3 GetRot(void) { return m_pCamera.rot; }
	D3DXVECTOR3 GetPos(void) { return m_pCamera.posV; }
	D3DXVECTOR3 GetPosR(void) { return m_pCamera.posR; }
	D3DXMATRIX GetMtxProjection(void) { return m_pCamera.mtxprojection; }
	int GetMode(void) { return m_pCamera.nMode; }
	bool GetShake(void) { return m_isShake; }

	// フラグメント
	bool GetIsRotation(void) { return m_isRotation; }
	bool GetFinishRotation(void) { return m_isStopRotation; }
	bool GetKeyFlag(void) { return m_isKey; }

private:
	// 定数宣言
	static constexpr int NUMKEY = 10;

	//*************************
	// イベントフレーム構造体
	//*************************
	struct EventData
	{
		bool isActive;		// イベント実行中か
		int	 frame;			// 経過フレーム
		int	 endFrame;		// 終了フレーム
		D3DXVECTOR3 startPosV;		// 開始視点
		D3DXVECTOR3 startPosR;		// 開始注視点
		D3DXVECTOR3 targetPosV;		// 目標視点
		D3DXVECTOR3 targetPosR;		// 目標注視点
	};


	//********************************
	// カメラアニメーションキー構造体
	//********************************
	struct AnimDataKey
	{
		float fPosVX;	// 視点X
		float fPosVY;	// 視点Y
		float fPosVZ;	// 視点Z

		float fPosRX;	// 注視点X
		float fPosRY;	// 注視点Y
		float fPosRZ;	// 注視点Z

		float fRotX;	// 向きX
		float fRotY;	// 向きY
		float fRotZ;	// 向きZ
		int nAnimFrame; // アニメーションのフレーム
		float fDistance;// カメラの距離
	};

	//**********************************
	// カメラアニメーションデータ構造体
	//**********************************
	struct AnimData
	{
		AnimDataKey KeyInfo[NUMKEY];	// 構造体
		int nNumKey; // キーの最大数
		bool isLoop;	// ループするかどうか
	};

	//*************************
	// カメラ構造体を定義
	//*************************
	struct Camera
	{
		D3DXMATRIX mtxprojection;	// プロジェクションマトリックス
		D3DXMATRIX mtxView;			// ビューマトリックス
		D3DXVECTOR3 posV, posR;		// 視点,注視点座標
		D3DXVECTOR3 rot;			// 角度
		D3DXVECTOR3 vecU;			// 法線ベクトル
		D3DXVECTOR3 posRDest;		// 目的座標
		float fDistance;			// カメラの距離
		int nMode;					// カメラのモード
		int nUseKey;				// アニメーション使用時に読み取るキー数
		AnimData m_AnimData;	// アニメーションデータ
	};

	EventData m_event;		// イベント用データ
	Camera m_pCamera;		// カメラ構造体変数

	int m_nShakeTime;				// 振動時間
	int m_nAnimNowKey;				// 現在キーNo

	bool m_isRotation;		// 回転したかどうか
	bool m_isStopRotation;	// 回転終了
	bool m_isSetPos;		// ボスが死んだかどうかのフラグ
	bool m_isShake;			// 振動するかどうか
	bool m_isKey;			// キー入力判定
	bool isAnimTime;		// アニメーション中かどうか

	D3DXVECTOR3 m_lastBossPos;		// ボスの最後の座標

};

#endif