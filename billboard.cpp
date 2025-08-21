//====================================
//
// ビルボード処理 [ billboard.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "billboard.h"
#include "manager.h"

//================================
// コンストラクタ
//================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_col = COLOR_WHITE;
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nIdxTexture = NULL;
	m_pVtxBuff = nullptr;
	m_mtxWorld = {};
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_isTests = false;
	m_FlashCount = NULL;
}
//================================
// デストラクタ
//================================
CBillboard::~CBillboard()
{
	// 無し
}
//================================
// 生成処理
//================================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fWidth, float fHeight)
{
	// インスタンス生成
	CBillboard* pBillboard = new CBillboard;

	// nullptrだったら
	if (pBillboard == nullptr) return nullptr;

	// オブジェクトセット
	pBillboard->SetPos(pos);
	pBillboard->SetSize(fWidth, fHeight);
	pBillboard->SetRot(rot);

	// 初期化失敗時
	if (FAILED(pBillboard->Init()))
	{
		// 失敗結果を返す
		return nullptr;
	}

	// ビルボードのポインタを返す
	return pBillboard;
}
//================================
// 初期化処理
//================================
HRESULT CBillboard::Init(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報のポインタ
	VERTEX_3D* pVtx = nullptr;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);

	// 各頂点の法線(ベクトル)の設定
	pVtx[0].nor = 
	pVtx[1].nor = 
	pVtx[2].nor = 
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f,-1.0f);	// 法線情報の設定

	// 頂点カラーの設定
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = COLOR_WHITE;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//================================
// 終了処理
//================================
void CBillboard::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		// 解放
		m_pVtxBuff->Release();

		// nullptr初期化
		m_pVtxBuff = nullptr;
	}

	// オブジェクトの破棄
	CObject::Release();
}
//================================
// 更新処理
//================================
void CBillboard::Update(void)
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx = nullptr;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);

	// 各頂点の法線(ベクトル)の設定
	pVtx[0].nor = 
	pVtx[1].nor = 
	pVtx[2].nor = 
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	// 法線情報

	// 頂点カラーの設定
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// アンロック
	m_pVtxBuff->Unlock();

}
//================================
// 描画処理
//================================
void CBillboard::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (m_isTests)
	{
		// Zテストを適用
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ビューマトリックスを宣言
	D3DXMATRIX mtxView;

	// ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// カメラの逆行列を設定
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// テクスチャを戻す
	pDevice->SetTexture(0, NULL);

	if (m_isTests)
	{
		// Zテストを戻す
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	// ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//================================
// テクスチャセット
//================================
void CBillboard::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// 割り当て
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\billboard_wepon.png");
}
//================================
// 点滅処理
//================================
void CBillboard::Flash(const int nMaxFlashTime, const int Digittime)
{
	// 頂点情報のポインタ
	VERTEX_3D* pVtx = nullptr;

	// 頂点バッファをロックし,頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 点滅カウントを加算
	m_FlashCount++;

	// カラー変数
	D3DXCOLOR col = COLOR_WHITE;

	// 点滅カウントと一致したとき
	if (m_FlashCount == Digittime)		
	{
		//頂点カラーの設定
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);

		// カラーセット
		SetCol(col);
	}
	else if (m_FlashCount == nMaxFlashTime)	// 最大継続時間と一致したとき
	{
		//頂点カラーの設定
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// カラーセット
		SetCol(col);

		// 初期値に戻す
		m_FlashCount = NULL;
	}

	//アンロック
	m_pVtxBuff->Unlock();

}
