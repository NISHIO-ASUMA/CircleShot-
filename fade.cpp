//====================================
//
// フェード処理 [ fade.cpp ]
// Author: Asuma Nishio
// 
//=====================================

//**************************
// インクルードファイル宣言
//**************************
#include "fade.h"
#include "manager.h"

//==============================
// コンストラクタ
//==============================
CFade::CFade()
{
	// 値のクリア
	m_pVtx = nullptr;
	m_col = COLOR_BLACK;
	m_fade = FADE_NONE;
	m_pScene = nullptr;
}
//==============================
// デストラクタ
//==============================
CFade::~CFade()
{
	// 無し
}
//==============================
// 初期化処理
//==============================
HRESULT CFade::Init(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	// 頂点情報のポインタ
	VERTEX_2D* pVtx = NULL;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f);

	// rhwの設定(1.0fで固定)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtx->Unlock();

	// 初期化結果を返す
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CFade::Uninit(void)
{
	// nullptrチェック
	if (m_pVtx != nullptr)
	{
		m_pVtx->Release();
		m_pVtx = nullptr;
	}
}
//==============================
// 更新処理
//==============================
void CFade::Update(void)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx = NULL;

	// 何もなかったら
	if (m_fade == FADE_NONE)
	{
		return;
	}

	// IN状態
	if (m_fade == FADE_IN)
	{
		// フェードイン状態
		m_col.a -= AlphaFade;

		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_fade = FADE_NONE;		// 何もしていない状態
		}
	}
	// OUT状態
	else if (m_fade == FADE_OUT)
	{
		// フェードアウト状態
		m_col.a += AlphaFade;

		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_fade = FADE_IN;

			// 次のモード設定
			CManager::SetScene(m_pScene);

			// ここで処理返す
			return;
		}
	}

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(m_col);
	pVtx[1].col = D3DXCOLOR(m_col);
	pVtx[2].col = D3DXCOLOR(m_col);
	pVtx[3].col = D3DXCOLOR(m_col);

	// アンロック
	m_pVtx->Unlock();
}
//==============================
// 描画処理
//==============================
void CFade::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//==============================
// 設定処理
//==============================
void CFade::SetFade(CScene * pNewScene)
{
	// タイプがNONEじゃ無かったら
	if (m_fade != FADE_NONE)
	{
		// 新しいシーンの破棄
		delete pNewScene;

		// nullptrにする
		pNewScene = nullptr;

		// ここで処理を返す
		return;
	}

	// 現在シーンをnullにする
	if (m_pScene != nullptr)
	{
		m_pScene = nullptr;
	}

	// nullptrなので新しいシーンを生成する
	if (m_pScene == nullptr)
	{
		// シーンをセットする
		m_pScene = pNewScene;

		// フェードアウト状態を作る
		m_fade = FADE_OUT;
	}
}
