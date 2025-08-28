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
		MODE_NONE = 0,
		MODE_PLAYER,
		MODE_LOCKON,
		MODE_MOUSE,
		MODE_EVENT,
		MOMDE_MAX
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

	// セッター
	void StartEventCamera(const D3DXVECTOR3& targetV, const D3DXVECTOR3& targetR, int endFrame);
	void ShakeCamera(int WaveTime);
	void SetIsRotation(bool isFlags) { m_isRotation = isFlags; }
	void SetFinishRotation(bool isFlags) { m_isStopRotation = isFlags; }
	void SetCameraMode(int nMode) { m_pCamera.nMode = nMode; }

	// ゲッター
	D3DXVECTOR3 GetRot(void) { return m_pCamera.rot; }
	D3DXMATRIX GetMtxProjection(void) { return m_pCamera.mtxprojection; }
	int GetMode(void) { return m_pCamera.nMode; }


	// フラグメント
	bool GetIsRotation(void) { return m_isRotation; }
	bool GetFinishRotation(void) { return m_isStopRotation; }

private:
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
		int nMode;				// カメラのモード
	};

	Camera m_pCamera;	// 構造体変数
	bool m_isRotation;	// 回転したかどうか
	bool m_isStopRotation;	// 回転終了

	D3DXVECTOR3 m_lastBossPos;		// ボスの最後の座標
	bool m_isSetPos;		// ボスが死んだかどうかのフラグ

	int m_nShakeTime;
	bool m_isShake;

	//*************************
	// イベントフレーム構造体
	//*************************
	struct EventData
	{
		bool isActive = false;	// イベント実行中か
		int	 frame = 0;			// 経過フレーム
		int	 endFrame = 0;		// 終了フレーム
		D3DXVECTOR3 startPosV;		// 開始視点
		D3DXVECTOR3 startPosR;		// 開始注視点
		D3DXVECTOR3 targetPosV;		// 目標視点
		D3DXVECTOR3 targetPosR;		// 目標注視点
	};

	EventData m_event;				// イベント用データ
};

#endif