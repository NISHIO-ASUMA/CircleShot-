//====================================
//
// 入力関数 [ input.cpp ]
// Author: Asuma Nishio
//
//=====================================

//********************************
// インクルードファイル宣言
//********************************
#include "input.h"
#include "main.h"

//********************************
// マクロ定義
//********************************
constexpr int PREVSTICK = 1000;// Lスティックのしきい値

//********************************
// 静的メンバ変数宣言
//********************************
LPDIRECTINPUT8 CInput::m_pInput = nullptr; // 入力情報

//=======================
// コンストラクタ
//=======================
CInput::CInput()
{
	// 値のクリア
	m_pDevice = NULL;
	m_pInput = NULL;
}
//=======================
// デストラクタ
//=======================
CInput::~CInput()
{
	// 無し
}
//=======================
// 初期化処理
//=======================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// NULLチェック
	if (m_pInput == NULL)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//=======================
// 終了処理
//=======================
void CInput::Uninit(void)
{
	// 入力デバイスの破棄
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();	// アクセス権の破棄
		m_pDevice->Release();	// 解放

		m_pDevice = nullptr;
	}

	// DirectInputオブジェクトの破棄
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}
//=======================
// 入力デバイスの取得
//=======================
LPDIRECTINPUTDEVICE8 CInput::GetInputDevice(void)
{
	return m_pDevice;
}

//====================================
// キーボードクラスのコンストラクタ
//====================================
CInputKeyboard::CInputKeyboard()
{
	// 値のクリア
	for (int nCnt = 0; nCnt < KEY_MAX; nCnt++)
	{
		m_aKeystate[nCnt] = {};
		m_aOldState[nCnt] = {};
	}

	m_pDevice = NULL;
	m_pInput = NULL;
	m_nKeyPressCount = NULL;
}
//====================================
// キーボードクラスのデストラクタ
//====================================
CInputKeyboard::~CInputKeyboard()
{
	// 無し
}
//====================================
// キーボードクラスの初期化処理
//====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 親クラスの初期化
	CInput::Init(hInstance, hWnd);

	// 入力デバイス生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))	
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}
//====================================
// キーボードクラスの終了処理
//====================================
void CInputKeyboard::Uninit(void)
{
	// 親クラスの終了処理
	CInput::Uninit();
}
//====================================
// キーボードクラスの更新処理
//====================================
void CInputKeyboard::Update(void)
{
	// キーボードの入力情報格納用変数
	BYTE aKeyState[KEY_MAX];

	for (int nCntkey = 0; nCntkey < KEY_MAX; nCntkey++)
	{
		m_aOldState[nCntkey] = m_aKeystate[nCntkey];	// キーボードのプレス情報を保存
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCnt = 0; nCnt < KEY_MAX; nCnt++)
		{
			m_aKeystate[nCnt] = aKeyState[nCnt];	// キーボードのプレス情報を保存
		}
	}
	else
	{
		m_pDevice->Acquire();			// キーボードのアクセス権を獲得
	}
}
//====================================
// キーボードのプレス情報の取得
//====================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeystate[nKey] & 0x80) ? true : false;		// 三項演算子を使用
}
//====================================
// キーボードのトリガー情報の取得
//====================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	// フラグ変数
	bool isTrigger = false;

	if (m_aKeystate[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		isTrigger = true;
	}

	// 結果を返す
	return isTrigger;
}
//====================================
// キーボードのリリース情報の取得
//====================================
bool CInputKeyboard::GetRelease(int nKey)
{
	// フラグ変数
	bool isRelease = false;

	if (m_aKeystate[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		isRelease = true;
	}

	// 結果を返す
	return isRelease;
}
//====================================
// キーボードのリピート情報の取得
//====================================
bool CInputKeyboard::GetRepeat(int nKey,int nMaxTime)
{
	bool isRepeat = false;

	// キーカウントを加算
	m_nKeyPressCount++;

	if (m_aOldState[nKey] & 0x80 && (m_aKeystate[nKey] & 0x80) && nMaxTime <= m_nKeyPressCount)
	{
		isRepeat = true;
		m_nKeyPressCount = 0;
	}

	return isRepeat;
}

//====================================
// ゲームパッドのコンストラクタ
//====================================
CJoyPad::CJoyPad()
{
	// 値のクリア
	m_joyKeyState = {};
	m_joyKeyStateTrigger = {};
	m_OldKeyState = {};
	m_pDevice = NULL;
	m_pInput = NULL;
	m_nPressCount = NULL;

	// 振動用変数
	m_isVibration = false;
	m_leftMotor = NULL;
	m_rightMotor = NULL;
	m_VibrationEndTime = NULL;
}
//====================================
// ゲームパッドのデストラクタ
//====================================
CJoyPad::~CJoyPad()
{
	// 無し
}
//====================================
// ゲームパッドの初期化処理
//====================================
HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// メモリのクリア
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	// メモリのクリア
	memset(&m_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// Xinputのステートを設定(有効化)
	XInputEnable(true);

	return S_OK;
}
//====================================
// ゲームパッドの終了処理
//====================================
void CJoyPad::Uninit(void)
{
	// 親クラスの終了処理
	CInput::Uninit();

	// Xinputのステートを無効化
	XInputEnable(false);
}
//====================================
// ゲームパッドの更新処理
//====================================
void CJoyPad::Update(void)
{
	// 前回入力値
	m_OldKeyState = m_joyKeyState;

	XINPUT_STATE joykeyState;			// 入力情報を取得

	// ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;				// 押したときの入力情報
		WORD OldButton = m_joyKeyState.Gamepad.wButtons;		// 1F前の入力情報

		m_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		m_joyKeyState = joykeyState;							// ジョイパッドのプレス情報を保存(格納)
	}
	else
	{
		// 状態リセット
		ZeroMemory(&m_joyKeyState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_joyKeyStateTrigger, sizeof(XINPUT_STATE));
	}
}
//====================================
// ゲームパッド振動関数
//====================================
void CJoyPad::SetVibration(int leftMotor, int rightMotor, int durationMs)
{
	m_leftMotor = leftMotor;	// 左のモーターの強さ
	m_rightMotor = rightMotor;  // 右モーターの強さ
	m_VibrationEndTime = GetTickCount64() + durationMs; // 継続時間
	m_isVibration = true;		// フラグを有効化

	// XInputを設定
	XINPUT_VIBRATION vibration = {};
	vibration.wLeftMotorSpeed = leftMotor;
	vibration.wRightMotorSpeed = rightMotor;
	XInputSetState(0, &vibration); // コントローラーに適応
}
//==========================================================================================================
// ゲームパッド振動更新処理
//==========================================================================================================
void CJoyPad::UpdateVibration(void)
{
	if (m_isVibration == true && GetTickCount64() >= m_VibrationEndTime)
	{// 振動時間が経過したら停止
		XINPUT_VIBRATION vibration = {};
		XInputSetState(0, &vibration);
		m_isVibration = false;
	}
}
//====================================
// ゲームパッドのプレス情報の取得
//====================================
bool CJoyPad::GetPress(JOYKEY Key)
{
	return (m_joyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//====================================
// ゲームパッドのトリガー情報の取得
//====================================
bool CJoyPad::GetTrigger(JOYKEY Key)
{
	return (m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//====================================
// ゲームパッドのリリース情報の取得
//====================================
bool CJoyPad::GetRelease(JOYKEY Key)
{
	// フラグ変数宣言
	bool isRelease = false;

	if (m_OldKeyState.Gamepad.wButtons & (0x01 << Key) && !((m_OldKeyState.Gamepad.wButtons & (0x01 << Key))))
	{
		isRelease = true;
	}

	// 結果を返す
	return false;
}
//====================================
// ゲームパッドのリピート情報の取得
//====================================
bool CJoyPad::GetRepeat(JOYKEY Key,int nMaXTime)
{
	// フラグ変数宣言
	bool isRepeat = false;

	// 今フレームもキーが押されている
	if (m_joyKeyState.Gamepad.wButtons & (0x01 << Key))
	{
		m_nPressCount++;

		if (nMaXTime <= m_nPressCount)
		{
			isRepeat = true;
			m_nPressCount = 0;
		}
	}
	else
	{
		m_nPressCount = 0;
	}

	// 結果を返す
	return isRepeat;
}
//====================================
// パッドのLスティック処理			
//====================================
bool CJoyPad::GetLeftStick(void)
{
	// ローカル変数宣言
	bool isLstick = false;

	// スティックの入力値がしきい値を超えていなければ
	if (m_joyKeyState.Gamepad.sThumbLX >=  PREVSTICK  ||
		m_joyKeyState.Gamepad.sThumbLX <= -PREVSTICK  ||
		m_joyKeyState.Gamepad.sThumbLY >=  PREVSTICK  ||
		m_joyKeyState.Gamepad.sThumbLY <= -PREVSTICK)
	{
		isLstick = true;
	}

	// 結果を返す
	return isLstick;
}
//====================================
// マウスのコンストラクタ
//====================================
CInputMouse::CInputMouse()
{
	// 値のクリア
	m_CurrentMouseState = {};
	m_PrevState = {};
	m_pDevice = NULL;
	m_pInput = NULL;
}
//====================================
// マウスのデストラクタ
//====================================
CInputMouse::~CInputMouse()
{
	// 無い
}
//====================================
// マウスの初期化処理
//====================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// 親クラスの初期化処理
	CInput::Init(hInstance,hWnd);

	if (FAILED(m_pInput->CreateDevice(
		GUID_SysMouse,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}

	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// 協調モードの設定
	if (FAILED(m_pDevice->SetCooperativeLevel(
		hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	//キーボードのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}
//====================================
// マウスの終了処理
//====================================
void CInputMouse::Uninit(void)
{
	// 親クラスの終了処理
	CInput::Uninit();
}
//====================================
// マウスの更新処理
//====================================
void CInputMouse::Update(void)
{
	// 過去の情報セット
	m_PrevState.lX = m_CurrentMouseState.lX;
	m_PrevState.lY = m_CurrentMouseState.lY;

	// 最新の情報を保存する
	m_PrevState = m_CurrentMouseState;

	// 最新のマウスの状態を更新
	HRESULT	hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);

	// 取得できなかった場合
	if (FAILED(hr))
	{
		// マウスデバイスの解放
		m_pDevice->Acquire();
	}

	// マウス座標を取得する
	POINT p;
	GetCursorPos(&p);

	// スクリーン座標をクライアント座標に変換する
	ScreenToClient(FindWindowA(CLASS_NAME, WINDOW_NAME), &p);

	m_CurrentMouseState.lX = p.x;
	m_CurrentMouseState.lY = p.y;
}
//====================================
// マウスのカーソル設定
//====================================
void CInputMouse::SetCursorVisibility(bool visible)
{
	// カーソルカウント
	static int cursurCount = 0;

	if (visible)
	{
		//カーソルを表示
		while (cursurCount < 0)
		{
			ShowCursor(TRUE);
			cursurCount++;
		}
	}
	else
	{
		//カーソルを非表示
		while (cursurCount >= 0)
		{
			ShowCursor(FALSE);
			cursurCount--;
		}
	}
}
//====================================
// マウスのトリガー情報を取得
//====================================
bool CInputMouse::GetTriggerDown(int button_type)
{
	if (!(m_PrevState.rgbButtons[button_type] & (0x80)) &&
		m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		return true;
	}

	return false;
}
//====================================
// マウスのリリース情報の取得
//====================================
bool CInputMouse::GetTriggerUp(int button_type)
{
	if (m_PrevState.rgbButtons[button_type] & (0x80) &&
		!(m_CurrentMouseState.rgbButtons[button_type] & (0x80)))
	{
		return true;
	}

	return false;
}
//====================================
// マウスのプレス情報の取得
//====================================
bool CInputMouse::GetPress(int button_type)
{
	return (m_CurrentMouseState.rgbButtons[button_type] & 0x80) ? true : false;
}
//====================================
// マウスの状態を取得
//====================================
bool CInputMouse::GetState(DIMOUSESTATE* mouseState)
{
	// 入力デバイスを取得
	LPDIRECTINPUTDEVICE8 pMouse = GetInputDevice();

	if (pMouse == NULL)
	{
		return false;
	}

	// マウスの状態を取得
	HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

	if (FAILED(hr))
	{
		// 入力デバイスがリセットされている場合、再取得を試みる
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			pMouse->Acquire();

			// 再取得を試みる
			hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

			if (FAILED(hr))
			{
				return false;
			}
		}
		else
		{
			//エラーの場合
			return false;
		}
	}

	return true; // 正常に取得できた場合

}
//====================================
// マウスホイールの値を取得
//====================================
BOOL CInputMouse::IsMouseWheelPresent(void)
{
	return (GetSystemMetrics(SM_MOUSEWHEELPRESENT) != 0);
}