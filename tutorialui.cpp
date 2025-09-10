//=============================================
//
// チュートリアルUI処理 [ tutorialui.cpp ]
// Author: Asuma Nishio
// 
// TODO : ここはUIを描画するクラス
//
//=============================================

//******************************
// インクルードファイル宣言
//******************************
#include "tutorialui.h"
#include "manager.h"
#include "texture.h"

//******************************
// 名前空間
//******************************
namespace TUTORIAL_UIINFO
{
	constexpr float MOVEDOWNVALUE = 5.0f;		// 移動速度
	constexpr float MAX_MOVEWIDTH = 1120.0f;	// 最大座標
}

//==============================
// コンストラクタ
//==============================
CTutorialUi::CTutorialUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nIdxTexture = NULL;
	m_nState = STATE_AWAIT;
	m_fAlpha = 1.0f;
}
//==============================
// デストラクタ
//==============================
CTutorialUi::~CTutorialUi()
{
	CObject2D::Uninit();
}
//==============================
// 生成処理
//==============================
CTutorialUi* CTutorialUi::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * pFileName,int nState)
{
	// インスタンス生成
	CTutorialUi* pTutoUi = new CTutorialUi;

	// インスタンス生成失敗時
	if (pTutoUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pTutoUi->Init()))
	{
		return nullptr;
	}

	// オブジェクト2Dの基本設定
	pTutoUi->SetPos(pos);
	pTutoUi->SetSize(fWidth, fHeight);
	pTutoUi->SetTexture(pFileName);
	pTutoUi->SetState(nState);

	// 生成されたポインタを返す
	return pTutoUi;
}
//==============================
// 初期化処理
//==============================
HRESULT CTutorialUi::Init(void)
{
	// オブジェクト2Dの初期化処理
	CObject2D::Init();

	// 頂点生成タイプを設定
	SetAnchor(CObject2D::ANCHORTYPE_CENTER);

	// 初期化結果を返す
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CTutorialUi::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObject2D::Uninit();
}
//==============================
// 更新処理
//==============================
void CTutorialUi::Update(void)
{
	// 現在座標を取得
	D3DXVECTOR3 NowPos = GetPos();

	//  種類分け
	switch (m_nState)
	{
	case STATE_AWAIT:

		// 状態変更
		m_nState = STATE_MOVE;

		break;

	case STATE_MOVE:

		// 移動量を加算
		NowPos.x -= TUTORIAL_UIINFO::MOVEDOWNVALUE;

		// 上限に達したら
		if (NowPos.x <= TUTORIAL_UIINFO::MAX_MOVEWIDTH)
		{
			// 横幅設定
			NowPos.x = TUTORIAL_UIINFO::MAX_MOVEWIDTH;

			// 状態変更
			m_nState = STATE_STOP;
		}
		break;

	case STATE_STOP:
		break;

	case STATE_EXIT:
		// α値を減少
		m_fAlpha -= 0.03f;

		if (m_fAlpha <= 0.0f)
		{
			m_fAlpha = 0.0f;
		}

		break;

	default:
		break;
	}

	// オブジェクトの設定
	SetPos(NowPos);
	SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

	// オブジェクト2Dの更新処理
	CObject2D::Update();
}
//==============================
// 描画処理
//==============================
void CTutorialUi::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャポインタ取得
	CTexture * pTexture = CManager::GetTexture();

	// 取得時,nullだったら
	if (pTexture == nullptr) return;

	// テクスチャ割り当て
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// オブジェクト2Dの描画処理
	CObject2D::Draw();
	
}
//==============================
// カラー判定を取得
//==============================
bool CTutorialUi::IsFinished() const
{
	return (m_fAlpha <= 0.0f);
}
//==============================
// テクスチャ割り当て処理
//==============================
void CTutorialUi::SetTexture(const char* pFileName)
{
	// テクスチャポインタを取得
	CTexture* pTexture = CManager::GetTexture();

	// 取得時,nullだったら
	if (pTexture == nullptr) return;

	// テクスチャ割り当て
	m_nIdxTexture = pTexture->Register(pFileName);
}
