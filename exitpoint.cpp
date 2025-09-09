//=====================================
//
// 出口ポイント処理 [ exitpoint.cpp ]
// Author: Asuma Nishio
// 
//=====================================

//**********************
// インクルードファイル
//**********************
#include "exitpoint.h"
#include "manager.h"
#include "texture.h"

//**********************
// 名前空間
//**********************
namespace EXITINFO
{
	constexpr float MOVEVALUE = 0.5f;	// 拡大量
	constexpr float MAXWIDTH = 40.0f;	// 最大拡大量
};

//==============================
// オーバーロードコンストラクタ
//==============================
CExitPoint::CExitPoint(int nPriority) : CObject3D(nPriority)
{
	// 値のクリア
	m_nIdxTex = NULL;
}
//==============================
// デストラクタ
//==============================
CExitPoint::~CExitPoint()
{
	// 無し
}
//==============================
// 生成処理
//==============================
CExitPoint* CExitPoint::Create(D3DXVECTOR3 pos, float fWidth)
{
	// インスタンス生成
	CExitPoint* pExit = new CExitPoint;
	if (pExit == nullptr) return nullptr;

	// オブジェクト設定
	pExit->SetPos(pos);
	pExit->SetSize(fWidth, fWidth);
	pExit->SetTexture();

	// 初期化失敗時
	if (FAILED(pExit->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pExit;
}
//==============================
// 初期化処理
//==============================
HRESULT CExitPoint::Init(void)
{
	// 親クラスの初期化処理
	CObject3D::Init();

	// 種類定義
	SetObjType(CObject:: TYPE_POINT);

	// 初期化結果を返す
	return S_OK;
}
//==============================
// 終了処理
//==============================
void CExitPoint::Uninit(void)
{
	// 終了処理
	CObject3D::Uninit();
}
//==============================
// 更新処理
//==============================
void CExitPoint::Update(void)
{
	// 座標を取得
	D3DXVECTOR3 pos = GetPos();

	// 現在の横幅取得
	float fWidth = GetWidth();

	// 徐々に加算
	fWidth += EXITINFO::MOVEVALUE;

	// 最大値を超えたら
	if (fWidth >= EXITINFO::MAXWIDTH) fWidth = EXITINFO::MAXWIDTH;

	// 反映
	SetSize(fWidth, fWidth);

	// 更新処理
	CObject3D::Update();
}
//==============================
// 描画処理
//==============================
void CExitPoint::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// 親クラスの描画処理
	CObject3D::Draw();
}
//==============================
// テクスチャ割り当て
//==============================
void CExitPoint::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();
	if (pTexture == nullptr) return;

	// テクスチャ割り当て
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\bullet002.png");
}
//==============================
// 当たり判定処理 ( 円判定 )
//==============================
bool CExitPoint::Collision(D3DXVECTOR3 * DestPos)
{
	// 中心座標を取得
	D3DXVECTOR3 pos = GetPos();

	// 半径
	float fRadius = GetWidth() * 0.5f;

	// 2点間の距離
	float dx = DestPos->x - pos.x;
	float dz = DestPos->z - pos.z;
	float distSq = dx * dx + dz * dz;

	// 半径の二乗と比較
	if (distSq <= fRadius * fRadius)
	{
		return true;	// 範囲内
	}

	return false;		// 範囲外
}