//====================================
//
// マネージャー処理 [ manager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "manager.h"
#include "score.h"
#include "time.h"
#include "objectX.h"
#include "billboard.h"
#include "block.h"
#include "meshdome.h"
#include "meshfield.h"
#include "player.h"
#include "meshimpact.h"
#include "gage.h"
#include "ui.h"
#include "title.h"
#include "game.h"

//**************************
// 静的メンバ変数宣言
//**************************
CRenderer* CManager::m_pRenderer = nullptr;				// レンダラーへのポインタ
CInputKeyboard* CManager::m_pInputKeyboard = nullptr;	// キーボードへのポインタ
CJoyPad* CManager::m_pJoyPad = nullptr;					// ジョイパッドクラスへのポインタ
CSound* CManager::m_pSound = nullptr;					// サウンドへのポインタ
CInputMouse* CManager::m_pInputMouse = nullptr;			// マウスへのポインタ
CTexture* CManager::m_pTexture = nullptr;				// テクスチャクラスへのポインタ
CCamera* CManager::m_pCamera = nullptr;					// カメラクラスへのポインタ
CLight* CManager::m_pLight = nullptr;					// ライトクラスへのポインタ
CScene* CManager::m_pScene = nullptr;
CFade* CManager::m_pFade = nullptr;

//===========================
// コンストラクタ
//===========================
CManager::CManager()
{
	// 無し
}
//===========================
// デストラクタ
//===========================
CManager::~CManager()
{
	// 無し
}
//===========================
// マネージャーの初期化処理
//===========================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// キーボードオブジェクトの生成処理
	m_pInputKeyboard = new CInputKeyboard;

	// 初期化に失敗したら
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		// -1を返す
		return -1;
	}

	// ジョイパッドオブジェクトの生成処理
	m_pJoyPad = new CJoyPad;

	// 初期化に失敗したら
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		// -1を返す
		return -1;
	}

	// マウスオブジェクトの生成処理
	m_pInputMouse = new CInputMouse;

	// 初期化に失敗したら
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		// -1を返す
		return -1;
	}

	// サウンドの生成処理
	m_pSound = new CSound;

	if (FAILED(m_pSound->Init(hWnd)))
	{
		// -1を返す
		return -1;
	}

	// カメラ生成
	m_pCamera = new CCamera;

	// 初期化に失敗したら
	if (FAILED(m_pCamera->Init()))
	{
		// -1を返す
		return -1;
	}

	// レンダラーの生成処理
	m_pRenderer = new CRenderer;

	// 初期化に失敗したら
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		// -1を返す
		return -1;
	}

	// ライト生成
	m_pLight = new CLight;

	// 初期化に失敗したら
	if (FAILED(m_pLight->Init()))
	{
		// -1を返す
		return -1;
	}

	// フェード生成
	m_pFade = new CFade;

	// 初期化失敗時
	if (FAILED(m_pFade->Init()))
	{
		// -1を返す
		return -1;
	}

	// テクスチャ生成
	m_pTexture = new CTexture;

	// テクスチャ全読み込み
	m_pTexture->Load();

	// シーンセット
	m_pFade->SetFade(new CTitle(true));

	return S_OK;
}
//===========================
// マネージャーの終了処理
//===========================
void CManager::Uninit(void)
{
	// 全オブジェクトの破棄
	CObject::ReleaseAll();

	// NULLチェック
	if (m_pInputKeyboard != nullptr)
	{
		// キーボードの終了処理
		m_pInputKeyboard->Uninit();
		
		// キーボードの破棄
		delete m_pInputKeyboard;

		// NULLにする
		m_pInputKeyboard = nullptr;
	}

	// NULLチェック
	if (m_pJoyPad != nullptr)
	{
		// ジョイパッドの終了処理
		m_pJoyPad->Uninit();
		
		// ジョイパッドの破棄
		delete m_pJoyPad;

		// NULLにする
		m_pJoyPad = nullptr;
	}

	// NULLチェック
	if (m_pInputMouse != nullptr)
	{
		// マウスの終了処理
		m_pInputMouse->Uninit();

		// マウスの棄
		delete m_pInputMouse;

		// NULLにする
		m_pInputMouse = nullptr;
	}

	// NULLチェック
	if (m_pSound != nullptr)
	{
		// サウンドの終了処理
		m_pSound->Uninit();

		// サウンドの破棄
		delete m_pSound;

		// NULLにする
		m_pSound = nullptr;
	}

	// カメラの破棄
	if (m_pCamera != nullptr)
	{
		// 終了処理
		m_pCamera->Uninit();

		// 破棄
		delete m_pCamera;

		// NULLにする
		m_pCamera = nullptr;
	}

	//  ライトの破棄
	if (m_pLight != nullptr)
	{
		// 終了処理
		m_pLight->Uninit();

		// 破棄
		delete m_pLight;

		// NULLにする
		m_pLight = nullptr;
	}

	// テクスチャ破棄
	if (m_pTexture != nullptr)
	{
		// すべてのテクスチャの破棄
		m_pTexture->UnLoad();

		// ポインタの破棄
		delete m_pTexture;

		// nullptr代入
		m_pTexture = nullptr;
	}

	// nullptrじゃない
	if (m_pScene != nullptr)
	{
		// 終了処理
		m_pScene->Uninit();

		// ポインタの破棄
		delete m_pScene;

		// nullptrにする
		m_pScene = nullptr;
	}

	// nullptrじゃない
	if (m_pFade != nullptr)
	{
		// 終了処理
		m_pFade->Uninit();

		// ポインタの破棄
		delete m_pFade;

		// nullptrにする
		m_pFade = nullptr;
	}

	// nullptrじゃない
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();

		delete m_pScene;

		m_pScene = nullptr;
	}

	// NULLチェック
	if (m_pRenderer != nullptr)
	{
		// レンダラーの終了処理
		m_pRenderer->Uninit();

		// レンダラーの破棄
		delete m_pRenderer;

		// NULLにする
		m_pRenderer = nullptr;
	}
}
//===========================
// マネージャーの更新処理
//===========================
void CManager::Update()
{
	// キーボードの更新処理
	m_pInputKeyboard->Update();

	// ジョイパッドの更新処理
	m_pJoyPad->Update();

	// マウスの更新処理
	m_pInputMouse->Update();

	// カメラ更新
	m_pCamera->Update();

	// フェードの更新
	m_pFade->Update();

	if (m_pScene != nullptr)
	{
		// シーンの更新
		m_pScene->Update();
	}

	// レンダラーの更新処理
	m_pRenderer->Update();
}
//===========================
// マネージャーの描画処理
//===========================
void CManager::Draw(void)
{
	// レンダラーの描画処理
	m_pRenderer->Draw();
}

//===========================
// シーンのセット
//===========================
void CManager::SetScene(CScene * pNewscene) // SetMode
{
	// nullptrじゃない
	if (m_pScene != nullptr)
	{
		// 終了処理
		m_pScene->Uninit();

		// ポインタの破棄
		delete m_pScene;

		// nullptrにする
		m_pScene = nullptr;

		// nullじゃない
		if (m_pSound)
		{
			// サウンドの停止
			m_pSound->StopSound();
		}

		// 全オブジェクト破棄
		CObject::ReleaseAll();
	}

	// もしシーンが無かったら
	if (m_pScene == nullptr)
	{
		// 新しいシーンをセットする
		m_pScene = pNewscene;

		// シーンの初期化
		if (FAILED(m_pScene->Init()))
		{
			// 失敗時
			MessageBox(GetActiveWindow(), "シーン初期化失敗", "例外スロー", MB_OK);

			// 破棄
			delete m_pScene;

			// nullptr代入
			m_pScene = nullptr;
		}
	}
}
//===========================
// 現在シーン取得
//===========================
CScene::MODE CManager::GetScene(void)
{
	// nullptrじゃない
	if (m_pScene)
		return m_pScene->GetScene(); // 現在シーン
	else
		return CScene::MODE_NONE;	 // 何もないシーン
}


//===========================
// レンダラーの取得
//===========================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//===========================
// キーボードの取得
//===========================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//===========================
// ジョイパッドの取得
//===========================
CJoyPad* CManager::GetJoyPad(void)
{
	return m_pJoyPad;
}
//===========================
// サウンドの取得
//===========================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}
//===========================
// マウスの取得
//===========================
CInputMouse* CManager::GetMouse(void)
{
	return m_pInputMouse;
}
//===========================
// テクスチャの取得
//===========================
CTexture* CManager::GetTexture(void)
{
	return m_pTexture;
}
//===========================
// カメラの取得
//===========================
CCamera* CManager::GetCamera(void)
{
	return m_pCamera;
}
//===========================
// ライトの取得
//===========================
CLight* CManager::GetLight(void)
{
	return m_pLight;
}
//===========================
// フェード取得
//===========================
CFade* CManager::GetFade(void)
{
	return m_pFade;
}
