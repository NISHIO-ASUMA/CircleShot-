//====================================
//
// 数字処理 [ number.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "number.h"
#include "manager.h"

//=================================
// コンストラクタ
//=================================
CNumber::CNumber()
{
	// 値のクリア
	m_pos = { VECTOR3_NULL };
	m_pVtxBuff = nullptr;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_TexU = 0.0f;
	m_TexU1 = 0.0f;
	m_TexV = 0.0f;
}
//=================================
// デストラクタ
//=================================
CNumber::~CNumber()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CNumber::Init(D3DXVECTOR3 pos,float fwidth,float fheight)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報のポインタ
	VERTEX_2D* pVtx;	

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - fwidth, pos.y - fheight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fwidth, pos.y - fheight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fwidth, pos.y + fheight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fwidth, pos.y + fheight, 0.0f);

	// rhwの設定(1.0fで固定)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// 頂点カラーの設定
	pVtx[0].col = COLOR_WHITE;
	pVtx[1].col = COLOR_WHITE;
	pVtx[2].col = COLOR_WHITE;
	pVtx[3].col = COLOR_WHITE;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(DIGIT_VALUE, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(DIGIT_VALUE, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=================================
// 終了処理
//=================================
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//=================================
// 更新処理
//=================================
void CNumber::Update(void)
{
	// 無し
}
//=================================
// 描画処理
//=================================
void CNumber::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// テクスチャ戻す
	pDevice->SetTexture(0, NULL);
}
//=================================
// 頂点座標設定処理
//=================================
void CNumber::SetPos(D3DXVECTOR3 pos)
{
	// 座標代入
	m_pos = pos;
}
//=================================
// サイズ処理
//=================================
void CNumber::SetSize(float fWidth, float fHeight)
{
	// メンバ変数に代入
	m_fWidth = fWidth;
	m_fHeight = fHeight;
}
//==================================
// 桁数計算処理
//==================================
void CNumber::SetDigit(int nDigit)
{
	// 頂点情報のポインタ
	VERTEX_2D* pVtx;

	// 頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の計算
	float TexU = nDigit * DIGIT_VALUE;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(TexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexU + DIGIT_VALUE, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(TexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(TexU + DIGIT_VALUE, 1.0f);

	// 頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
