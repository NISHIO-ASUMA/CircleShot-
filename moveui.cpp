//==============================================================
//
// カメラアニメーション時に適用するUI処理 [ moveui.cpp ]
// Author: Asuma Nishio
//
//==============================================================

//**********************
// インクルードファイル
//**********************
#include "moveui.h"
#include "manager.h"
#include "texture.h"

//=================================
// オーバーロードコンストラクタ
//=================================
CMoveUi::CMoveUi(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nIdxTexture = NULL;
}
//=================================
// デストラクタ
//=================================
CMoveUi::~CMoveUi()
{
	// 無し
}
//=================================
// 生成処理処理
//=================================
CMoveUi* CMoveUi::Create(D3DXVECTOR3 pos, const char* pFileName, MOVETYPE type)
{
	// インスタンス生成
	CMoveUi* pMoveUi = new CMoveUi;
	if (pMoveUi == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pMoveUi->Init()))
	{
		return nullptr;
	}

	// 2Dオブジェクト設定
	pMoveUi->SetPos(pos);
	pMoveUi->SetSize(SCREEN_WIDTH * 0.5f, 30.0f);
	pMoveUi->SetTexture(pFileName);
	pMoveUi->m_nMoveType = type;
	pMoveUi->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pMoveUi->SetDrawType(1);

	// 生成されたポインタ
	return pMoveUi;
}
//=================================
// 初期化処理
//=================================
HRESULT CMoveUi::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CMoveUi::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//=================================
// 更新処理
//=================================
void CMoveUi::Update(void)
{
	// 現在座標を取得
	D3DXVECTOR3 NowPos = GetPos();

	// 画面中央座標
	float fCenterPos = SCREEN_WIDTH * 0.5f;
	float fSpeed = 10.0f;		// 移動スピード

	switch (m_nMoveType)
	{
	case MOVETYPE_RIGHT: // 右から中央へ

		if (NowPos.x > fCenterPos)
		{
			NowPos.x -= fSpeed;

			if (NowPos.x <= fCenterPos)
			{
				NowPos.x = fCenterPos;
				m_nMoveType = MOVETYPE_CENTER; // 到達したら中央固定
			}
			SetPos(NowPos);
		}

		break;

	case MOVETYPE_LEFT:   // 左から中央へ

		if (NowPos.x < fCenterPos)
		{
			NowPos.x += fSpeed;

			if (NowPos.x >= fCenterPos)
			{
				NowPos.x = fCenterPos;
				m_nMoveType = MOVETYPE_CENTER; // 到達したら中央固定
			}

			SetPos(NowPos);
		}
		break;

	case MOVETYPE_CENTER: // 中央で止まる

		NowPos.x = fCenterPos;
		SetPos(NowPos);

		break;
	}


	// カメラアニメーションが終わったら
	if (CManager::GetCamera()->GetAnim())
	{
		// 半分より上の座標なら上に,半分より下の座標なら下に消えていく
		float fCenterY = SCREEN_HEIGHT * 0.5f;

		if (NowPos.y < fCenterY)
			NowPos.y -= 3.0f;   // 上へ
		else
			NowPos.y += 3.0f;   // 下へ

		SetPos(NowPos);

		// 画面外に出たら破棄
		if (NowPos.y < -30.0f || NowPos.y > SCREEN_HEIGHT + 30.0f)
		{
			Uninit();

			return;
		}
	}


	// 親クラス更新処理
	CObject2D::Update();
}
//=================================
// 描画処理
//=================================
void CMoveUi::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャセット
	CTexture* pTexture = CManager::GetTexture();

	// 割り当て
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// オブジェクトの描画
	CObject2D::Draw();
}
//=================================
// テクスチャ処理
//=================================
void CMoveUi::SetTexture(const char* pRegistername)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// nullじゃなかったら
	if (pTexture != nullptr)
	{
		// テクスチャ設定
		m_nIdxTexture = pTexture->Register(pRegistername);
	}
}