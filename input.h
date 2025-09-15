//====================================
//
// 入力関数 [ input.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _INPUT_H_ // このマクロ定義がされてなかったら
#define _INPUT_H_ // 2重インクルード防止のマクロ定義

//*******************************
// 入力親クラスを定義
//*******************************
class CInput
{
public:
	// コンストラクタ・デストラクタ
	CInput();
	~CInput();

	// 仮想・純粋仮想関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

	// ゲッター
	LPDIRECTINPUTDEVICE8 GetInputDevice(void);

protected:
	static LPDIRECTINPUT8 m_pInput; // 入力変数
	LPDIRECTINPUTDEVICE8 m_pDevice; // 入力デバイス
};

//*******************************
// キーボードクラスを定義
//*******************************
class CInputKeyboard : public CInput
{
public:
	// コンストラクタ・デストラクタ
	CInputKeyboard();
	~CInputKeyboard();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// ゲッター
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey,int nMaxTime);

private:
	static inline constexpr int KEY_MAX = 256;

	BYTE m_aKeystate[KEY_MAX]; // キー入力状態
	BYTE m_aOldState[KEY_MAX]; // 過去の入力内容を保存

	int m_nKeyPressCount;
};

//*******************************
// ゲームパッドクラスを定義
//*******************************
class CJoyPad : public CInput
{
public:
	//*********************************
	// ジョイパッドのキーの列挙型
	//*********************************
	enum JOYKEY
	{
		JOYKEY_UP,			 // 十字キー(上)
		JOYKEY_DOWN,		 // 十字キー(下)
		JOYKEY_LEFT,		 // 十字キー(左)
		JOYKEY_RIGHT,		 // 十字キー(右)
		JOYKEY_START,		 // スタートキー
		JOYKEY_BACK,		 // バックキー
		JOYKEY_LS,			 // L3(Lスティック)
		JOYKEY_RS,			 // R3(Rスティック)
		JOYKEY_LEFT_B,		 // LBキー
		JOYKEY_RIGHT_B,		 // RBキー
		JOYKEY_LEFT_TRIGGER, // LTキー
		JOYKEY_RIGHT_TRIGGER,// RTキー
		JOYKEY_A,			 // Aボタン
		JOYKEY_B,			 // Bボタン
		JOYKEY_X,			 // Xボタン
		JOYKEY_Y,			 // Yボタン
		JOYKEY_MAX			 // パッドの最大数
	};

	// コンストラクタ・デストラクタ
	CJoyPad();
	~CJoyPad();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void UpdateVibration(void);

	// セッター
	void SetVibration(int leftMotor, int rightMotor, int durationMs);

	// ゲッター
	bool GetPress(JOYKEY Key);
	bool GetTrigger(JOYKEY Key);
	bool GetRelease(JOYKEY Key);
	bool GetRepeat(JOYKEY Key, int nMaXTime);
	bool GetLeftStick(void);

	XINPUT_STATE* GetStickAngle(void) { return &m_joyKeyState; }

private:
	XINPUT_STATE m_joyKeyState;		   // ジョイパッドのプレス情報
	XINPUT_STATE m_OldKeyState;		   // 過去のジョイパッド入力情報
	XINPUT_STATE m_joyKeyStateTrigger; // ジョイパッドのトリガー情報
	int m_nPressCount;

	//********************
	// 振動関数
	//********************
	int m_leftMotor; // 左モーターの強さ
	int m_rightMotor; // 右モーターの強さ
	DWORD m_VibrationEndTime; // 振動終了時刻
	bool m_isVibration;   // 振動中かどうか
};

//*******************************
// マウスクラスを定義
//*******************************
class CInputMouse : public CInput
{
public:
	//********************
	// マウスの列挙型
	//********************
	enum MOUSE
	{
		MOUSE_LEFT = 0,
		MOUSE_RIGHT,
		MOUSE_MAX
	};

	// コンストラクタ・デストラクタ
	CInputMouse();
	~CInputMouse();

	// メンバ関数
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// セッター
	void SetCursorVisibility(bool visible);

	// ゲッター
	bool GetTriggerDown(int button_type);
	bool GetTriggerUp(int button_type);
	bool GetPress(int button_type);
	bool GetState(DIMOUSESTATE* mouseState);
	D3DXVECTOR2 GetMouseVelocity() { return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY); }
	D3DXVECTOR2 GetMouseOldVelocity() { return D3DXVECTOR2((float)m_PrevState.lX, (float)m_PrevState.lY); }
	BOOL IsMouseWheelPresent(void);

private:
	DIMOUSESTATE m_PrevState;	 
	DIMOUSESTATE m_CurrentMouseState;
};
#endif