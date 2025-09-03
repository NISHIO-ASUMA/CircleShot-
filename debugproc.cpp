//===========================================
//
// デバッグプロセス処理 [ debubgproc.cpp ]
// Author: Asuma Nishio
//
//===========================================

//***********************
// インクルードファイル
//***********************
#include "debugproc.h"
#include <time.h>
#include <stdio.h>
#include "manager.h"

//***********************************
// 静的メンバ変数
//***********************************
LPD3DXFONT CDebugproc::m_pFont = nullptr;  // フォントへのポインタ
char CDebugproc::m_aStr[MAX_WORD] = {};	   // 文字列を格納するバッファ
bool CDebugproc::m_isUse = false;		   // 使用しているか

//===============================
// コンストラクタ
//===============================
CDebugproc::CDebugproc()
{
	// 無し
}
//===============================
// デストラクタ
//===============================
CDebugproc::~CDebugproc()
{
	// 無し
}
//===============================
// デバッグプロセスの初期化処理
//===============================
HRESULT CDebugproc::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// デバッグ表示用のフォントを設定
	D3DXCreateFont(pDevice, FontSize, 0, 0, 0,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &m_pFont);

	// 文字列クリア
	memset(m_aStr, 0, sizeof(m_aStr));

	// 使用状態時
	m_isUse = true;

	return S_OK;
}
//===============================
// デバッグプロセスの終了処理
//===============================
void CDebugproc::Uninit(void)
{
	// NULLチェック
	if (m_pFont != nullptr)
	{
		// 解放
		m_pFont->Release();

		// nullptrにする
		m_pFont = nullptr;
	}
}
//===============================
// デバッグプロセスの更新処理
//===============================
void CDebugproc::Update(void)
{
	// キー入力で表示切替
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F1))
	{
		m_isUse = m_isUse ? false : true;
	}
}
//===============================
// デバッグプロセスの描画処理
//===============================
void CDebugproc::Draw(int PosX,int PosY)
{
#ifdef _DEBUG
	if (m_isUse)
	{
		// ウィンドウレクト
		RECT rect = { PosX,PosY,SCREEN_WIDTH,SCREEN_HEIGHT };

		// フォントの生成
		m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));

		// バッファのクリア
		memset(m_aStr, 0, sizeof(m_aStr));
	}
#endif
}
//===============================
// フォント描画関数
//===============================
void CDebugproc::Print(const char* fmt, ...)
{
	// 変数宣言
	va_list list;

	// 描画開始
	va_start(list, fmt);

	// 描画の種類分け
	vsprintf_s(m_aStr, sizeof(m_aStr), fmt, list);

	// 終了
	va_end(list);

	// 文字列にコピー
	va_copy(list, m_aStr);
}